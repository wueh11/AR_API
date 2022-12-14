#include "yaPlayer.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaCamera.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

#include "yaUIManager.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaPlayerUpper.h"
#include "yaPlayerLower.h"
#include "yaPlayerKnifeSight.h"
#include "yaPlayerKnife.h"
#include "yaBullet.h"
#include "yaGrenade.h"

#include "yaPixelImageObject.h"

#include "yaColliderHorizontal.h"
#include "yaColliderVertical.h"

namespace ya
{
	Player::Player()
		: mSpeed(250.0f)
		, mArmsDirection({ 1.0f, 0.0f })
		, mUpper(nullptr)
		, mLower(nullptr)
	{
		SetName(L"Player");
		SetPos({ 150.0f, 200.0f });
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 24.0f, 36.0f });
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		Scene* playScene = SceneManager::GetPlayScene();

		mLower = new PlayerLower();
		AddChild(mLower);
		playScene->AddGameObject(mLower, eColliderLayer::Player);

		mUpper = new PlayerUpper();
		AddChild(mUpper);
		playScene->AddGameObject(mUpper, eColliderLayer::Player);
		
		PlayerKnifeSight* knifeSight = new PlayerKnifeSight();
		AddChild(knifeSight);
		playScene->AddGameObject(knifeSight, eColliderLayer::Player_Projecttile);


		ColliderHorizontal* colliderH = new ColliderHorizontal();
		AddChild(colliderH);
		playScene->AddGameObject(colliderH, eColliderLayer::Collider);

		ColliderVertical* colliderV = new ColliderVertical();
		AddChild(colliderV);
		playScene->AddGameObject(colliderV, eColliderLayer::Collider);

		AddComponent(new Collider());
		mRigidbody = AddComponent<Rigidbody>();
	}

	void Player::Tick()
	{
		GameObject::Tick();

		if (mMoveState.bJump && mRigidbody->isGround())
		{
			mMoveState.bJump = false;
			mMoveState.bDownside = false;
			mState = mBeforeState;
		}

		switch (mState)
		{
		case ya::Player::State::IDLE:
			Idle();
			break;
		case ya::Player::State::WALK:
			Walk();
			break;
		case ya::Player::State::JUMP:
			Jump();
			break;
		case ya::Player::State::SIT:
			Sit();
			break;
		case ya::Player::State::FRONT_TO_UPSIDE:
			break;
		case ya::Player::State::UPSIDE:
			Upside();
			break;
		case ya::Player::State::UPSIDE_TO_FRONT:
			break;
		case ya::Player::State::FRONT_TO_DOWNSIDE:
			break;
		case ya::Player::State::DOWNSIDE:
			Downside();
			break;
		case ya::Player::State::DOWNSIDE_TO_FRONT:
			break;
		case ya::Player::State::SHOOT:
			Shoot();
			break;
		case ya::Player::State::KNIFE:
			Knife();
			break;
		case ya::Player::State::BOMB:
			Bomb();
			break;
		case ya::Player::State::DIE:
			Die();
			break;
		case ya::Player::State::REVIVAL:
			Revival();
			break;
		case ya::Player::State::RESET:
			Reset();
			break;
		default:
			break;
		}
	}

	void Player::Render(HDC hdc)
	{
		wchar_t szFloat[50] = {};
		std::wstring str = L"[" + std::to_wstring((int)mState) + L"] " + std::to_wstring(GetPos().x) + L", " + std::to_wstring(GetPos().y);
		swprintf_s(szFloat, 50, str.c_str());
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 10, szFloat, strLen);

		std::wstring jumpstr = L"Jump : " + std::to_wstring(mMoveState.bJump);
		swprintf_s(szFloat, 50, jumpstr.c_str());
		TextOut(hdc, 600, 100, szFloat, strLen);

		std::wstring sitstr = L"Sit : " + std::to_wstring(mMoveState.bSit);
		swprintf_s(szFloat, 50, sitstr.c_str());
		TextOut(hdc, 600, 120, szFloat, strLen);

		std::wstring strUpside = L"Upside : " + std::to_wstring(mMoveState.bUpside);
		swprintf_s(szFloat, 50, strUpside.c_str());
		TextOut(hdc, 600, 140, szFloat, strLen);

		std::wstring strDownside = L"Downside : " + std::to_wstring(mMoveState.bDownside);
		swprintf_s(szFloat, 50, strDownside.c_str());
		TextOut(hdc, 600, 160, szFloat, strLen);

		std::wstring strKnife = L"Knife : " + std::to_wstring(mMoveState.bKnife);
		swprintf_s(szFloat, 50, strKnife.c_str());
		TextOut(hdc, 600, 180, szFloat, strLen);

		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{
	}

	void Player::OnCollisionStay(Collider* other)
	{
	}

	void Player::OnCollisionExit(Collider* other)
	{
	}

	void Player::Idle()
	{
		//mMoveState.Clear();
		mBeforeState = State::IDLE;

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}

		if (KEY_PRESS(eKeyCode::UP))
		{
			mState = State::UPSIDE;
			return;
		}

		if (KEY_PRESS(eKeyCode::DOWN))
		{
			mState = State::SIT;
			return;
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
			return;
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			if (mMoveState.bKnife)
				mState = State::KNIFE;
			else
				mState = State::SHOOT;
			return;
		}

		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}

		if (KEY_DOWN(eKeyCode::P))
		{
			mControlState.bAlive = false;
			mState = State::DIE;
			return;
		}

		if (KEY_DOWN(eKeyCode::R))
		{
			mControlState.bAlive = false;
			mState = State::RESET;
			return;
		}
	}

	void Player::Walk()
	{
		mMoveState.bWalk = true;
		mBeforeState = State::WALK;

		Vector2 pos = GetPos();

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
		}

		if (KEY_PRESS(eKeyCode::LEFT))
		{
			pos.x -= mSpeed * Time::DeltaTime() * (mMoveState.bSit ? 0.5f : 1.0f);
			mMoveState.bLeft = true;

		}
		else if (KEY_PRESS(eKeyCode::RIGHT))
		{
			pos.x += mSpeed * Time::DeltaTime() * (mMoveState.bSit ? 0.5f : 1.0f);
			mMoveState.bLeft = false;
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			if (mMoveState.bKnife)
				mState = State::KNIFE;
			else
				mState = State::SHOOT;
			return;
			return;
		}

		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}

		SetPos(pos);

		if (KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			mState = State::IDLE;
			mMoveState.bWalk = false;
			return;
		}
	}

	void Player::Jump()
	{
		if (!mMoveState.bJump)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y = -560.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			
			mMoveState.bJump = true;
		}

		mMoveState.bFall = (mRigidbody->GetVelocity().y > 0);

	/*	if (mRigidbody->isGround())
		{
			mMoveState.bJump = false;
			mMoveState.bDownside = false;
			mState = mBeforeState;
			return;
		}*/

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			if (mMoveState.bKnife)
				mState = State::KNIFE;
			else
				mState = State::SHOOT;
			return;
		}

		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
		}

		if (KEY_PRESS(eKeyCode::DOWN))
		{
			mState = State::DOWNSIDE;
		}
	}

	void Player::Sit()
	{
		mBeforeState = State::SIT;
		mMoveState.bSit = true;

		if (KEY_UP(eKeyCode::DOWN))
		{
			mMoveState.bSit = false;
			mState = State::IDLE;
			return;
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			if (mMoveState.bKnife)
				mState = State::KNIFE;
			else
				mState = State::SHOOT;
			return;
		}

		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mMoveState.bSit = false;
			mState = State::JUMP;
			return;
		}
	}

	void Player::Upside()
	{
		mBeforeState = State::UPSIDE;
		mMoveState.bUpside = true;

		if (KEY_UP(eKeyCode::UP))
		{
			mMoveState.bUpside = false;
			mState = State::IDLE;
			return;
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			mState = State::SHOOT;
			return;
		}

		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
			return;
		}
	}

	void Player::Downside()
	{
		mBeforeState = State::DOWNSIDE;
		mMoveState.bDownside = true;

		if(!mMoveState.bJump)
		{
			mMoveState.bDownside = false;
			mState = State::IDLE;
			return;
		}

		if (KEY_UP(eKeyCode::DOWN))
		{
			mMoveState.bDownside = false;
			mState = State::JUMP;
			return;
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			mState = State::SHOOT;
			return;
		}

		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}
	}

	void Player::Shoot()
	{
		OnShoot();
		mState = mBeforeState;
	}

	void Player::Knife()
	{
		OnKnife();
		mState = mBeforeState;
	}

	void Player::Bomb()
	{
		OnBomb();
		mState = mBeforeState;
	}

	void Player::Die()
	{
		mControlState.bInvincible = true;
		mControlState.bPlayable = false;
		mControlState.bAlive = false;

		if (Time::Timer(L"die", 3.0f))
		{
			mState = State::REVIVAL;
		}
	}

	void Player::Revival()
	{
		mControlState.bInvincible = false;
		mControlState.bPlayable = true;
		mControlState.bAlive = true;
		mControlState.bRevival = true;

		Collider* collider = GetComponent<Collider>();
		collider->SetActive(true);

		mInfo.arms = eArms::Pistol;
		mInfo.armsCount = -1;
		mInfo.bombCount = 10;

		if (Time::Timer(L"revival", 0.2f))
		{
			mControlState.bRevival = false;
			mState = State::IDLE;
		}
	}

	void Player::Reset()
	{
		SetPos({ 150.0f, 200.0f });

		//Camera::SetLookPosition();
		mInfo.arms = eArms::Pistol;
		mInfo.armsCount = -1;
		mInfo.bombCount = 10;

		mState = State::IDLE;
	}

	void Player::OnShoot()
	{
		Bullet* bullet = new Bullet();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(bullet, eColliderLayer::Player_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerSize = GetSize() / 2.0f;

		Vector2 bulletSize = bullet->GetSize();

		mArmsDirection = Vector2({ 1.0f, 0.0f });

		float dir = 0.0f;
		if (mMoveState.bUpside)
			dir = -90.0f;
		else if (mMoveState.bDownside)
			dir = 90.0f;
		else if (mMoveState.bLeft)
			dir = -180.0f;

		Vector2 offset = { 0.0f, -30.0f };
		if (mMoveState.bUpside || mMoveState.bDownside)
			offset.x = 0.0f;
		else if (mMoveState.bLeft)
			offset.x = -30.0f;
		else
			offset.x = 30.0f;

		if (mMoveState.bSit)
			offset.y = 0.0f;
		else
			offset.y = -20.0f;

		bullet->SetPos(playerPos + playerSize - (bulletSize / 2.0f) + offset);
		bullet->SetDirection(math::Rotate(mArmsDirection, dir));

		if(mInfo.arms != eArms::Pistol)
			mInfo.armsCount--;
	}

	void Player::OnKnife()
	{
		PlayerKnife* knife = new PlayerKnife();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(knife, eColliderLayer::Player_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerSize = GetSize() / 2.0f;
		Vector2 knifeSize = knife->GetSize();


		Vector2 offset = Vector2::Zero;
		if (mMoveState.bLeft)
			offset.x = -60.0f;
		else
			offset.x = 60.0f;

		knife->SetPos(playerPos + playerSize - (knifeSize / 2.0f) + offset);
	}

	void Player::OnBomb()
	{
		if (mInfo.bombCount == 0)
			return;
		
		mInfo.bombCount--;
		
		{
			Grenade* grenade = new Grenade();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(grenade, eColliderLayer::Player_Projecttile);

			Vector2 playerPos = GetPos();
			Vector2 playerSize = GetSize() / 2.0f;
			Vector2 grenadeSize = grenade->GetSize();

			mArmsDirection = Vector2({ 0.5f, -0.5f });

			float dir = 0.0f;
			if (mMoveState.bLeft)
				dir = 270.0f;

			Vector2 offset = Vector2::Zero;
			offset.x = -10.0f;

			grenade->SetPos(playerPos + playerSize - (grenadeSize / 2.0f) + offset);
			grenade->SetDirection(math::Rotate(mArmsDirection, dir));
		}
	}

	void Player::PickupArms(eArms arms, UINT bulletCount)
	{
		if (mInfo.arms == arms)
			mInfo.armsCount += bulletCount;
		else
			mInfo.armsCount = bulletCount;

		mInfo.arms = arms;
	}

	void Player::Attacked()
	{
		mState = State::DIE;

		mUpper->Attacked();

		Collider* collider = GetComponent<Collider>();
		collider->SetActive(false);
	}
}