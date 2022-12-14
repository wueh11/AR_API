#include "yaPlayerLower.h"
#include "yaPlayer.h"

#include "yaResources.h"
#include "yaInput.h"
#include "yaImage.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

namespace ya
{
	PlayerLower::PlayerLower()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
		SetName(L"PlayerLower");
		SetPos({ 0.0f, 0.0f });
		SetScale(Vector2::One);
		SetSize({ 20.0f, 15.0f });
		SetOffset({ 2.0f, 30.0f });
	}

	PlayerLower::~PlayerLower()
	{
	}

	void PlayerLower::Initialize()
	{
		GameObject* player = GetOwner();
		SetScale(player->GetScale());


		if (mImage == nullptr)
			mImage = Resources::Load<Image>(L"PlayerLower", L"..\\Resources\\Image\\Player\\player_lower.bmp");

		mAnimator = new Animator();

		//Right
		{
			mAnimator->CreateAnimation(L"IdleRight", mImage, Vector2(0.0f, 0.0f), Vector2(21.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.05f);
			mAnimator->CreateAnimation(L"WalkRight", mImage, Vector2(0.0f, 35.0f), Vector2(33.0f, 20.0f), Vector2(0.0f, 0.0f), 12, 0.05f);
			mAnimator->CreateAnimation(L"JumpRight", mImage, Vector2(0.0f, 78.0f), Vector2(22.0f, 24.0f), Vector2(2.0f, 0.0f), 6, 0.05f);
			mAnimator->CreateAnimation(L"JumpMoveRight", mImage, Vector2(0.0f, 129.0f), Vector2(35.0f, 21.0f), Vector2(0.0f, 0.0f), 6, 0.15f);
		}

		//Left
		{
			mAnimator->CreateAnimation(L"IdleLeft", mImage, Vector2(0.0f, 17.0f), Vector2(21.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.05f);
			mAnimator->CreateAnimation(L"WalkLeft", mImage, Vector2(0.0f, 56.0f), Vector2(33.0f, 20.0f), Vector2(0.0f, 0.0f), 12, 0.05f);
			mAnimator->CreateAnimation(L"JumpLeft", mImage, Vector2(0.0f, 103.0f), Vector2(22.0f, 24.0f), Vector2(2.0f, 0.0f), 6, 0.05f);
			mAnimator->CreateAnimation(L"JumpMoveLeft", mImage, Vector2(0.0f, 151.0f), Vector2(35.0f, 21.0f), Vector2(0.0f, 0.0f), 6, 0.15f);
		}
	
		mAnimator->Play(L"IdleRight", true);
		AddComponent(mAnimator);

		Collider* collider = new Collider();
		collider->SetSize(GetSize());
		collider->SetScale(GetScale());
		collider->SetOffset({ 0.0f, 0.0f });
		//AddComponent(collider);
	}

	void PlayerLower::Tick()
	{
		GameObject::Tick();

		Player* player = dynamic_cast<Player*>(GetOwner());
		mMoveState = player->GetMoveState();

		Vector2 pos = player->GetPos() + GetOffset();
		
		if (mMoveState.bSit)
			return;

		/* = player->IsLeft();
		bool mMoveState.bJump = player->IsJumping();
		bool mMoveState.bFall = player->IsFalling();
		bool bSit = player->IsSitting();*/

		switch (mState)
		{
		case ya::PlayerLower::State::IDLE:
			Idle();
			break;
		case ya::PlayerLower::State::WALK:
			Walk();
			break;
		case ya::PlayerLower::State::JUMP:
			Jump();
			break;
		case ya::PlayerLower::State::FALL:
			Fall();
			break;
		case ya::PlayerLower::State::JUMPMOVE:
			JumpMove();
			break;
		default:
			break;
		}

		SetPos(pos);
	}

	void PlayerLower::Render(HDC hdc)
	{
		if (mMoveState.bSit)
			return;

		/*Player* player = dynamic_cast<Player*>(GetOwner());
		bool mMoveState.bJump = player->IsJumping();*/

		//wchar_t szFloat[50] = {};

		////std::wstring res = (mMoveState.bJump ? L"TRUE" : L"FALSE");
		//int nState = (int)mState;
		//std::wstring strForce = L"state : " + std::to_wstring(nState);
		//swprintf_s(szFloat, 50, strForce.c_str());
		//int strLen = wcsnlen_s(szFloat, 50);
		//TextOut(hdc, 600, 300, szFloat, strLen);

		GameObject::Render(hdc);
	}

	void PlayerLower::OnCollisionEnter(Collider* other)
	{
	}

	void PlayerLower::OnCollisionStay(Collider* other)
	{
	}

	void PlayerLower::OnCollisionExit(Collider* other)
	{
	}

	void PlayerLower::Idle()
	{
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			mAnimator->Play(L"WalkLeft", true, true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"WalkRight", true);
		}

		if (KEY_PRESS(eKeyCode::LEFT)
			|| KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			if (mMoveState.bLeft)
				mAnimator->Play(L"JumpLeft", false, true);
			else
				mAnimator->Play(L"JumpRight", false);
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
			return;
		}
	}
	void PlayerLower::Walk()
	{
		if (KEY_UP(eKeyCode::LEFT)
			|| KEY_UP(eKeyCode::RIGHT))
		{
			if (mMoveState.bLeft)
				mAnimator->Play(L"IdleLeft", true, true);
			else
				mAnimator->Play(L"IdleRight", true);

			mState = State::IDLE;
			return;
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			if (mMoveState.bLeft)
				mAnimator->Play(L"JumpMoveLeft", false, true);
			else
				mAnimator->Play(L"JumpMoveRight", false);
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMPMOVE;
		}
	}
	void PlayerLower::Jump()
	{
		if(!mMoveState.bJump)
		{
			mState = State::IDLE;
			return;
		}

		if (mMoveState.bFall)
		{
			if (mMoveState.bLeft)
				mAnimator->Play(L"JumpLeft", false, false);
			else
				mAnimator->Play(L"JumpRight", false, true);

			mState = State::FALL;
		}
	}
	void PlayerLower::Fall()
	{
		if (!mMoveState.bJump)
		{
			if (mMoveState.bLeft)
				mAnimator->Play(L"IdleLeft", true, true);
			else
				mAnimator->Play(L"IdleRight", true);

			mState = State::IDLE;
		}
	}

	void PlayerLower::JumpMove()
	{
		if (!mMoveState.bJump)
		{
			/*if ()
				mAnimator->Play(L"IdleLeft", true, true);
			else
				mAnimator->Play(L"IdleRight", true);*/

			mState = State::IDLE;
		}
	}
}