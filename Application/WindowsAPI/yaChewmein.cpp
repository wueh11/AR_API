#include "yaChewmein.h"

#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaTime.h"
#include "yaCamera.h"
#include "yaInput.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"
#include "yaChewmeinEyeSight.h"
#include "yaChewmeinAttackSight.h"
#include "yaChewmeinAttack.h"

#include "yaChewmeinProjecttile.h"

namespace ya
{
	Chewmein::Chewmein()
		: Monster()
		, mState(eState::IDLE)
	{
		SetName(L"Chewmein");
		SetPos({ 600.0f, 200.0f });
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 32.0f, 40.0f });

		mSpeed = 300.0f;
		mStatus.SetHp(40);

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"Chewmein", L"..\\Resources\\Image\\Monster\\Chewmein\\chewmein.bmp");

			mAnimator = AddComponent<Animator>();

			mAnimator->CreateAnimation(L"WalkLeft", mImage, Vector2(0.0f, 11.0f), Vector2(54.0f, 46.0f), Vector2(0.0f, -10.0f), 7, 0.1f);
			mAnimator->CreateAnimation(L"WalkRight", mImage, Vector2(0.0f, 57.0f), Vector2(54.0f, 46.0f), Vector2(0.0f, -10.0f), 7, 0.1f);

			mAnimator->CreateAnimation(L"JumpLeft", mImage, Vector2(0.0f, 129.0f), Vector2(55.0f, 52.0f), Vector2(0.0f, -10.0f), 2, 0.5f);
			mAnimator->CreateAnimation(L"JumpRight", mImage, Vector2(0.0f, 182.0f), Vector2(55.0f, 52.0f), Vector2(0.0f, -10.0f), 2, 0.5f);

			mAnimator->CreateAnimation(L"TurnLeft", mImage, Vector2(0.0f, 251.0f), Vector2(55.0f, 45.0f), Vector2(0.0f, -10.0f), 2, 0.1f);
			mAnimator->CreateAnimation(L"TurnRight", mImage, Vector2(0.0f, 297.0f), Vector2(55.0f, 45.0f), Vector2(0.0f, -10.0f), 2, 0.1f);

			mAnimator->CreateAnimation(L"AttackLeft", mImage, Vector2(0.0f, 357.0f), Vector2(76.0f, 52.0f), Vector2(-20.0f, -22.0f), 13, 0.06f);
			mAnimator->CreateAnimation(L"AttackRight", mImage, Vector2(0.0f, 411.0f), Vector2(76.0f, 52.0f), Vector2(20.0f, -22.0f), 13, 0.06f);

			mAnimator->GetCompleteEvent(L"AttackLeft") = std::bind(&Chewmein::OnAttackComplete, this);
			mAnimator->GetCompleteEvent(L"AttackRight") = std::bind(&Chewmein::OnAttackComplete, this);
			
			mAnimator->CreateAnimation(L"AttackBubbleLeft", mImage, Vector2(0.0f, 479.0f), Vector2(57.0f, 46.0f), Vector2(0.0f, -12.0f), 4, 0.1f);
			mAnimator->CreateAnimation(L"AttackBubbleRight", mImage, Vector2(0.0f, 526.0f), Vector2(57.0f, 46.0f), Vector2(0.0f, -12.0f), 4, 0.1f);

			mAnimator->GetCompleteEvent(L"AttackBubbleLeft") = std::bind(&Chewmein::OnIdle, this);
			mAnimator->GetCompleteEvent(L"AttackBubbleRight") = std::bind(&Chewmein::OnIdle, this);

			mAnimator->CreateAnimation(L"DieLeft", mImage, Vector2(0.0f, 588.0f), Vector2(76.0f, 57.0f), Vector2(0.0f, -24.0f), 27, 0.05f);
			mAnimator->CreateAnimation(L"DieRight", mImage, Vector2(0.0f, 646.0f), Vector2(76.0f, 57.0f), Vector2(0.0f, -24.0f), 27, 0.1f);

			mAnimator->GetCompleteEvent(L"DieLeft") = std::bind(&Chewmein::Death, this);
			mAnimator->GetCompleteEvent(L"DieRight") = std::bind(&Chewmein::Death, this);

			mAnimator->Play(L"WalkLeft", true);
		}

		Scene* playScene = SceneManager::GetPlayScene();

		ChewmeinEyeSight* eyeSight = new ChewmeinEyeSight();
		AddChild(eyeSight);
		playScene->AddGameObject(eyeSight, eColliderLayer::Event);

		ChewmeinAttackSight* attackSight = new ChewmeinAttackSight();
		AddChild(attackSight);
		playScene->AddGameObject(attackSight, eColliderLayer::Event);
	}

	Chewmein::~Chewmein()
	{
		/*for (GameObject* object : mChildren)
		{
			if (object == nullptr)
				continue;

			delete object;
			object = nullptr;
		}*/
	}

	void Chewmein::Initialize()
	{
		Monster::Initialize();
	}

	void Chewmein::Tick()
	{
		Monster::Tick();

		if (mStatus.alive && mStatus.hp <= 0)
		{
			mStatus.Die();
			mState = eState::DIE;
		}

		if (KEY_DOWN(eKeyCode::T))
		{
			mState = eState::ATTACK;
		}

		switch (mState)
		{
		case ya::Chewmein::eState::IDLE:
			Idle();
			break;
		case ya::Chewmein::eState::WALK_FRONT:
			WalkFront();
			break;
		case ya::Chewmein::eState::WALK_BACK:
			WalkBack();
			break;
		case ya::Chewmein::eState::TURN:
			Turn();
			break;
		case ya::Chewmein::eState::JUMP:
			Jump();
			break;
		case ya::Chewmein::eState::ATTACK:
			Attack();
			break;
		case ya::Chewmein::eState::ATTACK_BUBBLE:
			AttackBubble();
			break;
		case ya::Chewmein::eState::DIE:
			Die();
			break;
		default:
			break;
		}
	}

	void Chewmein::Render(HDC hdc)
	{
		Vector2 pos = Camera::CalculatePos(GetPos());

		wchar_t szFloat[50] = {};
		std::wstring str = L"[" + std::to_wstring((int)mState) + L"] HP:" + std::to_wstring((int)mStatus.hp);
		swprintf_s(szFloat, 50, str.c_str());
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, pos.x - 20.0f, pos.y - 80.0f, szFloat, strLen);

		Monster::Render(hdc);
	}

	void Chewmein::OnCollisionEnter(Collider* other)
	{
		Monster::OnCollisionEnter(other);
	}

	void Chewmein::OnCollisionStay(Collider* other)
	{
	}

	void Chewmein::OnCollisionExit(Collider* other)
	{
	}

	void Chewmein::Idle()
	{
	}

	void Chewmein::WalkFront()
	{
		Vector2 pos = GetPos();

		if (mMoveState.bLeft)
			pos.x -= mSpeed * Time::DeltaTime();
		else
			pos.x += mSpeed * Time::DeltaTime();

		SetPos(pos);
	}

	void Chewmein::WalkBack()
	{
		Vector2 pos = GetPos();

		GameObject* target = mTarget;
		Vector2 targetPos = target->GetPos();

		if (mMoveState.bLeft)
		{
			pos.x += mSpeed * Time::DeltaTime();
			if (pos.x > targetPos.x + 270.0f)
				mState = eState::WALK_FRONT;
		}
		else
		{
			pos.x -= mSpeed * Time::DeltaTime();
			if (pos.x < targetPos.x - 270.0f)
				mState = eState::WALK_FRONT;
		}

		SetPos(pos);
	}

	void Chewmein::Turn()
	{
	}

	void Chewmein::Jump()
	{
	}

	void Chewmein::Attack()
	{
		if (mMoveState.bLeft)
			mAnimator->Play(L"AttackLeft", false);
		else
			mAnimator->Play(L"AttackRight", false, true);

		ChewmeinAttack* attack = new ChewmeinAttack();
		Scene* playScene = SceneManager::GetPlayScene();
		AddChild(attack);
		playScene->AddGameObject(attack, eColliderLayer::Monster_Projecttile);

		mState = eState::IDLE;
	}

	void Chewmein::AttackBubble()
	{
		ChewmeinProjecttile* projecttile = new ChewmeinProjecttile();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(projecttile, eColliderLayer::Monster_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerSize = GetSize() / 2.0f;

		Vector2 projecttileSize = projecttile->GetSize();
		Vector2 projecttilePos = projecttile->GetPos();

		Vector2 offset = { -20.0f, -30.0f };
		projecttile->SetPos(playerPos + playerSize - (projecttileSize / 2.0f) + offset);

		if (mMoveState.bLeft)
			mAnimator->Play(L"AttackBubbleLeft", false);
		else
			mAnimator->Play(L"AttackBubbleRight", false, true);

		mState = eState::IDLE;
	}

	void Chewmein::Die()
	{
		if (mMoveState.bLeft)
			mAnimator->Play(L"DieLeft", false);
		else
			mAnimator->Play(L"DieRight", false, true);

		mState = eState::IDLE;
	}

	void Chewmein::OnIdle()
	{
		if (mMoveState.bLeft)
			mAnimator->Play(L"WalkLeft", true);
		else
			mAnimator->Play(L"WalkRight", true, true);
	}

	void Chewmein::OnAttack()
	{
	}

	void Chewmein::OnAttackComplete()
	{
		int a = 0;
		WalkBack();
		//mState = eState::WALK_FRONT;
	}
}