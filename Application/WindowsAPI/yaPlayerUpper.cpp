#include "yaPlayerUpper.h"

#include "yaResources.h"
#include "yaInput.h"
#include "yaImage.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"
#include "yaCollider.h"

#include "yaPlayer.h"

namespace ya
{
	PlayerUpper::PlayerUpper()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
		SetName(L"PlayerUpper");
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
		SetSize({ 20.0f, 20.0f });
		SetOffset({ 2.0f, -8.0f });
	}

	PlayerUpper::~PlayerUpper()
	{
	}

	void PlayerUpper::Initialize()
	{
		GameObject* player = GetOwner();
		SetScale(player->GetScale());

		//Upper
		if (mImage == nullptr)
			mImage = Resources::Load<Image>(L"PlayerUpper", L"..\\Resources\\Image\\Player\\player_upper_pistol.bmp");

		mAnimator = new Animator();
		CreateAnimation();
		mAnimator->Play(L"Idle-Right-Pistol", true);

		AddComponent(mAnimator);

		mCollider = new Collider();
		mCollider->SetSize(GetSize());
		mCollider->SetScale(GetScale());
		mCollider->SetOffset({ 0.0f, 0.0f });
		//AddComponent(mCollider);
	}

	void PlayerUpper::Tick()
	{
		GameObject::Tick();

		Player* player = dynamic_cast<Player*>(GetOwner());

		mMoveState = player->GetMoveState();
		mControlState = player->GetControlState();
		mArms = player->GetArms();
			
		if (!mControlState.bAlive)
			mState = State::DIE;

		Vector2 pos = player->GetPos() + GetOffset();

		switch (mState)
		{
		case ya::PlayerUpper::State::IDLE:
			Idle();
			break;
		case ya::PlayerUpper::State::WALK:
			Walk();
			break;
		case ya::PlayerUpper::State::JUMP:
			Jump();
			break;
		case ya::PlayerUpper::State::WALKJUMP:
			WalkJump();
			break;
		case ya::PlayerUpper::State::SIT:
			Sit();
			break;
		case ya::PlayerUpper::State::SITWALK:
			SitWalk();
			break;
		case ya::PlayerUpper::State::UPSIDE:
			Upside();
			break;
		case ya::PlayerUpper::State::UPSIDE_TO_FRONT:
			UpsideToFront();
			break;
		case ya::PlayerUpper::State::FRONT_TO_DOWNSIDE:
			FrontToDownside();
			break;
		case ya::PlayerUpper::State::DOWNSIDE:
			Downside();
			break;
		case ya::PlayerUpper::State::DOWNSIDE_TO_FRONT:
			DownsideToFront();
			break;
		case ya::PlayerUpper::State::SHOOT:
			Shoot();
			break;
		case ya::PlayerUpper::State::KNIFE:
			Knife();
			break;
		case ya::PlayerUpper::State::BOMB:
			Bomb();
			break;
		case ya::PlayerUpper::State::DIE:
			Die();
			break;
		case ya::PlayerUpper::State::REVIVAL:
			Revival();
			break;
		default:
			break;
		}

		SetPos(pos);
	}

	void PlayerUpper::Render(HDC hdc)
	{
		//Player* player = dynamic_cast<Player*>(GetOwner());

		//wchar_t szFloat[50] = {};

		////std::wstring res = (mMoveState.bJump ? L"TRUE" : L"FALSE");
		//int nState = (int)mState;
		//std::wstring strForce = L"state : " + std::to_wstring(nState);
		//swprintf_s(szFloat, 50, strForce.c_str());
		//int strLen = wcsnlen_s(szFloat, 50);
		//TextOut(hdc, 600, 300, szFloat, strLen);

		GameObject::Render(hdc);
	}

	void PlayerUpper::OnCollisionEnter(Collider* other)
	{
	}

	void PlayerUpper::OnCollisionStay(Collider* other)
	{
	}

	void PlayerUpper::OnCollisionExit(Collider* other)
	{
	}

	void PlayerUpper::CreateAnimation()
	{
		//Pistol
		{
			{ //Upper
				
				{ //Right
					mAnimator->CreateAnimation(L"Idle-Right-Pistol", mImage, Vector2(0.0f, 0.0f), Vector2(31.0f, 29.0f), Vector2(10.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Walk-Right-Pistol", mImage, Vector2(0.0f, 62.0f), Vector2(34.0f, 29.0f), Vector2(8.0f, 0.0f), 12, 0.1f);
					mAnimator->CreateAnimation(L"Jump-Right-Pistol", mImage, Vector2(0.0f, 125.0f), Vector2(33.0f, 26.0f), Vector2(0.0f, -16.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"JumpMove-Right-Pistol", mImage, Vector2(0.0f, 182.0f), Vector2(34.0f, 35.0f), Vector2(2.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Knife1-Right-Pistol", mImage, Vector2(0.0f, 318.0f), Vector2(43.0f, 48.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"Knife2-Right-Pistol", mImage, Vector2(0.0f, 419.0f), Vector2(50.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"Bomb-Right-Pistol", mImage, Vector2(0.0f, 486.0f), Vector2(30.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Shoot-Front-Right-Pistol", mImage, Vector2(0.0f, 256.0f), Vector2(52.0f, 30.0f), Vector2(40.0f, 0.0f), 10, 0.04f);

					mAnimator->CreateAnimation(L"Upside-Right-Pistol", mImage, Vector2(0.0f, 548.0f), Vector2(34.0f, 26.0f), Vector2(10.0f, -10.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Front-Upside-Right-Pistol", mImage, Vector2(0.0f, 606.0f), Vector2(36.0f, 32.0f), Vector2(12.0f, -18.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Upside-Right-Pistol", mImage, Vector2(0.0f, 672.0f), Vector2(31.0f, 66.0f), Vector2(4.0f, -60.0f), 10, 0.04f);

					mAnimator->CreateAnimation(L"Downside-Right-Pistol", mImage, Vector2(54.0f, 808.0f), Vector2(26.0f, 30.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Front-Downside-Right-Pistol", mImage, Vector2(0.0f, 808.0f), Vector2(26.0f, 30.0f), Vector2(0.0f, 0.0f), 3, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Downside-Right-Pistol", mImage, Vector2(0.0f, 888.0f), Vector2(25.0f, 52.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
				
					mAnimator->GetCompleteEvent(L"Front-Upside-Right-Pistol") = std::bind(&PlayerUpper::OnUpside, this);
					mAnimator->GetCompleteEvent(L"Front-Downside-Right-Pistol") = std::bind(&PlayerUpper::OnDownside, this);
				}

				{ //Left
					mAnimator->CreateAnimation(L"Idle-Left-Pistol", mImage, Vector2(0.0f, 30.0f), Vector2(31.0f, 29.0f), Vector2(-10.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Walk-Left-Pistol", mImage, Vector2(0.0f, 93.0f), Vector2(34.0f, 29.0f), Vector2(-8.0f, 0.0f), 12, 0.1f);
					mAnimator->CreateAnimation(L"Jump-Left-Pistol", mImage, Vector2(0.0f, 152.0f), Vector2(33.0f, 26.0f), Vector2(0.0f, -16.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"JumpMove-Left-Pistol", mImage, Vector2(0.0f, 219.0f), Vector2(34.0f, 35.0f), Vector2(2.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Knife1-Left-Pistol", mImage, Vector2(0.0f, 368.0f), Vector2(43.0f, 48.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"Knife2-Left-Pistol", mImage, Vector2(0.0f, 453.0f), Vector2(50.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"Bomb-Left-Pistol", mImage, Vector2(0.0f, 517.0f), Vector2(30.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Shoot-Front-Left-Pistol", mImage, Vector2(0.0f, 286.0f), Vector2(52.0f, 30.0f), Vector2(-40.0f, 0.0f), 10, 0.04f);

					mAnimator->CreateAnimation(L"Upside-Left-Pistol", mImage, Vector2(0.0f, 576.0f), Vector2(34.0f, 26.0f), Vector2(-6.0f, -12.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Front-Upside-Left-Pistol", mImage, Vector2(0.0f, 639.0f), Vector2(36.0f, 32.0f), Vector2(-12.0f, -18.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Upside-Left-Pistol", mImage, Vector2(0.0f, 739.0f), Vector2(31.0f, 66.0f), Vector2(-6.0f, -60.0f), 10, 0.04f);

					mAnimator->CreateAnimation(L"Downside-Left-Pistol", mImage, Vector2(54.0f, 848.0f), Vector2(26.0f, 30.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Front-Downside-Left-Pistol", mImage, Vector2(0.0f, 48.0f), Vector2(26.0f, 30.0f), Vector2(0.0f, 0.0f), 3, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Downside-Left-Pistol", mImage, Vector2(0.0f, 944.0f), Vector2(25.0f, 52.0f), Vector2(0.0f, 0.0f), 6, 0.1f);

					mAnimator->GetCompleteEvent(L"Front-Upside-Left-Pistol") = std::bind(&PlayerUpper::OnUpside, this);
					mAnimator->GetCompleteEvent(L"Front-Downside-Left-Pistol") = std::bind(&PlayerUpper::OnDownside, this);
				}
			}
			
			{ //Sit
				{ //Right
					mAnimator->CreateAnimation(L"Front-Sit-Right-Pistol", mImage, Vector2(0.0f, 999.0f), Vector2(34.0f, 41.0f), Vector2(8.0f, 3.0f), 3, 0.04f);
					mAnimator->GetCompleteEvent(L"Front-Sit-Right-Pistol") = std::bind(&PlayerUpper::OnSit, this);
					
					mAnimator->CreateAnimation(L"Sit-Turn-Right-Pistol", mImage, Vector2(0.0f, 1085.0f), Vector2(23.0f, 25.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Sit-Idle-Right-Pistol", mImage, Vector2(0.0f, 1139.0f), Vector2(39.0f, 24.0f), Vector2(12.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Walk-Right-Pistol", mImage, Vector2(0.0f, 1189.0f), Vector2(39.0f, 24.0f), Vector2(10.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Shoot-Right-Pistol", mImage, Vector2(0.0f, 1241.0f), Vector2(55.0f, 27.0f), Vector2(30.0f, -10.0f), 10, 0.04f);
					mAnimator->CreateAnimation(L"Sit-Bomb-Right-Pistol", mImage, Vector2(0.0f, 1299.0f), Vector2(43.0f, 28.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife1-Right-Pistol", mImage, Vector2(0.0f, 1357.0f), Vector2(43.0f, 34.0f), Vector2(0.0f, 0.0f), 7, 0.2f);

					mAnimator->CreateAnimation(L"Revival-Pistol", mImage, Vector2(0.0f, 1756.0f), Vector2(34.0f, 240.0f), Vector2(0.0f, 0.0f), 7, 0.02f);
				}

				{ //Left
					mAnimator->CreateAnimation(L"Front-Sit-Left-Pistol", mImage, Vector2(0.0f, 1042.0f), Vector2(34.0f, 41.0f), Vector2(-8.0f, 3.0f), 3, 0.04f);
					mAnimator->GetCompleteEvent(L"Front-Sit-Left-Pistol") = std::bind(&PlayerUpper::OnSit, this);
					
					mAnimator->CreateAnimation(L"Sit-Turn-Left-Pistol", mImage, Vector2(0.0f, 1112.0f), Vector2(23.0f, 25.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Sit-Idle-Left-Pistol", mImage, Vector2(0.0f, 1164.0f), Vector2(39.0f, 24.0f), Vector2(-14.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Walk-Left-Pistol", mImage, Vector2(0.0f, 1214.0f), Vector2(39.0f, 24.0f), Vector2(-10.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Shoot-Left-Pistol", mImage, Vector2(0.0f, 1270.0f), Vector2(55.0f, 27.0f), Vector2(-30.0f, -10.0f), 10, 0.04f);
					mAnimator->CreateAnimation(L"Sit-Bomb-Left-Pistol", mImage, Vector2(0.0f, 1328.0f), Vector2(43.0f, 28.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife1-Left-Pistol", mImage, Vector2(0.0f, 1392.0f), Vector2(43.0f, 34.0f), Vector2(0.0f, 0.0f), 7, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife2-Left-Pistol", mImage, Vector2(0.0f, 1461.0f), Vector2(51.0f, 33.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
				}
			}
		}

		//Heavy Machinegun
		{

		}

		{ // °øÅë
			mAnimator->CreateAnimation(L"Die-Right-Pistol", mImage, Vector2(0.0f, 1674.0f), Vector2(40.0f, 40.0f), Vector2(0.0f, 0.0f), 19, 0.04f);
			mAnimator->CreateAnimation(L"Die-Left-Pistol", mImage, Vector2(0.0f, 1715.0f), Vector2(40.0f, 40.0f), Vector2(0.0f, 0.0f), 19, 0.04f);
		}
	}

	void PlayerUpper::Idle()
	{
		if (!mControlState.bPlayable)
			return;

		if (mMoveState.bJump)
		{
			mState = State::IDLE;
			return;
		}

		if (KEY_DOWN(eKeyCode::LEFT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Walk-Left-Pistol", true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Walk-Right-Pistol", true);
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}

		FrontToSit();
		FrontToUpside();

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Jump-Left-Pistol", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Jump-Right-Pistol", false);
			}
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
			return;
		}

		{ // pistol
			if (KEY_DOWN(eKeyCode::LCTRL))
			{
				if (mMoveState.bLeft)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Front-Left-Pistol", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Front-Right-Pistol", false);
				}
			}

			if (KEY_PRESS(eKeyCode::LCTRL))
			{
				mState = State::SHOOT;
				return;
			}
		}

		/*if (KEY_PRESS(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}*/
	}

	void PlayerUpper::Walk()
	{
		if (KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}

			mState = State::IDLE;
			return;
		}

		FrontToUpside();

		{ // shoot
			if (KEY_DOWN(eKeyCode::LCTRL))
			{
				if (mMoveState.bLeft)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Front-Left-Pistol", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Front-Right-Pistol", false);
				}
			}

			if (KEY_PRESS(eKeyCode::LCTRL))
			{
				mState = State::SHOOT;
				return;
			}
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Jump-Left-Pistol", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Jump-Right-Pistol", false);
			}
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::WALKJUMP;
			return;
		}

		if (KEY_PRESS(eKeyCode::DOWN))
		{
			mState = State::FRONT_TO_DOWNSIDE;
			return;
		}

		if (KEY_PRESS(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}
	}

	void PlayerUpper::Jump()
	{
		if (!mMoveState.bJump)
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}

			mState = State::IDLE;
			return;
		}

		FrontToUpside();
		FrontToDownside();

		if (KEY_DOWN(eKeyCode::DOWN))
		{
			if (mArms == eArms::Pistol)
			{
				if (mMoveState.bLeft)
					mAnimator->Play(L"Downside-Left-Pistol", false, true);
				else
					mAnimator->Play(L"Downside-Right-Pistol", false);
			}
		}

		if (KEY_PRESS(eKeyCode::LCTRL))
		{
			mState = State::SHOOT;
		}

		if (KEY_PRESS(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
		}
	}
	
	void PlayerUpper::WalkJump()
	{
		if (!mMoveState.bJump)
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}

			mState = State::WALK;
			return;
		}

		{ // shoot
			if (KEY_DOWN(eKeyCode::LCTRL))
			{
				if (mMoveState.bLeft)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Front-Left-Pistol", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Front-Right-Pistol", false);
				}
			}

			if (KEY_PRESS(eKeyCode::LCTRL))
			{
				mState = State::SHOOT;
				return;
			}
		}

		if (KEY_PRESS(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
		}
	}
	
	void PlayerUpper::FrontToSit()
	{
		if (KEY_DOWN(eKeyCode::DOWN))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Sit-Left-Pistol", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Sit-Right-Pistol", false);
			}
		}

		if (KEY_PRESS(eKeyCode::DOWN))
		{
			mState = State::SIT;
			return;
		}
	}

	void PlayerUpper::Sit()
	{
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Left-Pistol", true, true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Right-Pistol", true);
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::SITWALK;
			return;
		}

		if (KEY_UP(eKeyCode::DOWN))
		{
			Vector2 offset = GetOffset();
			offset.y = -8.0f;
			SetOffset(offset);

			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}

			mState = State::IDLE;
			return;
		}
		
		{ // jump
			if (KEY_DOWN(eKeyCode::SPACE))
			{
				if (mMoveState.bLeft)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Jump-Left-Pistol", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Jump-Right-Pistol", false);
				}
			}

			if (KEY_PRESS(eKeyCode::SPACE))
			{
				Vector2 offset = GetOffset();
				offset.y = -8.0f;
				SetOffset(offset);

				mState = State::JUMP;
				return;
			}
		}

		{ // Shoot
			if (KEY_DOWN(eKeyCode::LCTRL))
			{
				if (mMoveState.bLeft)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Sit-Shoot-Left-Pistol", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Sit-Shoot-Right-Pistol", false);
				}
			}

			if (KEY_PRESS(eKeyCode::LCTRL))
			{
				mState = State::SHOOT;
				return;
			}
		}
	}

	void PlayerUpper::SitToFront()
	{
	}

	void PlayerUpper::SitWalk()
	{
		if (KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Sit-Idle-Left-Pistol", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Sit-Idle-Right-Pistol", true);
			}
			
			mState = State::SIT;
			return;
		}

		if (KEY_UP(eKeyCode::DOWN))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}
			mState = State::IDLE;
			return;
		}
	}

	void PlayerUpper::FrontToUpside()
	{
		if (KEY_DOWN(eKeyCode::UP))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false);
			}
		}

		if (KEY_PRESS(eKeyCode::UP))
		{
			mState = State::UPSIDE;
		}
	}

	void PlayerUpper::Upside()
	{
		if (KEY_UP(eKeyCode::UP))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, false);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false, true);
			}

			mState = State::IDLE;
			return;
		}

		{ // shoot
			if (KEY_DOWN(eKeyCode::LCTRL))
			{
				if (mMoveState.bLeft)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Upside-Left-Pistol", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Upside-Right-Pistol", false);
				}
			}

			if (KEY_PRESS(eKeyCode::LCTRL))
			{
				mState = State::SHOOT;
				return;
			}
		}

		/*
		if (KEY_PRESS(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
		}*/
	}

	void PlayerUpper::UpsideToFront()
	{
		if (KEY_UP(eKeyCode::UP))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false);
			}
		}

		if (KEY_PRESS(eKeyCode::UP))
		{
			mState = State::IDLE;
		}
	}

	void PlayerUpper::FrontToDownside()
	{
		if (!mMoveState.bJump)
		{
			mState = State::IDLE;
			return;
		}

		if (KEY_PRESS(eKeyCode::LCTRL))
		{
			mState = State::SHOOT;
			return;
		}

		{ // downside
			if (KEY_UP(eKeyCode::DOWN))
			{
				if (mMoveState.bLeft)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Idle-Left-Pistol", true, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Idle-Right-Pistol", true);
				}
				mState = State::IDLE;
				return;
			}

			if (KEY_PRESS(eKeyCode::DOWN))
			{
				mState = State::DOWNSIDE;
				return;
			}
		}

		if (mMoveState.bLeft)
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Front-Downside-Left-Pistol", false, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Front-Downside-Right-Pistol", false);
		}
	}

	void PlayerUpper::Downside()
	{
		if (KEY_UP(eKeyCode::DOWN))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, false);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false, true);
			}

			mState = State::DOWNSIDE_TO_FRONT;
			return;
		}

		if (KEY_DOWN(eKeyCode::LEFT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Left-Pistol", true, true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Right-Pistol", true);
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}
	}
	void PlayerUpper::DownsideToFront()
	{
		if (mMoveState.bLeft)
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Idle-Left-Pistol", true, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Idle-Right-Pistol", true);
		}

		mState = State::IDLE;
	}
	
	void PlayerUpper::Shoot()
	{
		if (KEY_UP(eKeyCode::LCTRL))
		{
			mState = State::IDLE;
		}

		if (mMoveState.bSit)
		{
			mState = State::SIT;
		} 
		else if (mMoveState.bUpside)
		{
			mState = State::UPSIDE;
		}
		else if (mMoveState.bDownside)
		{
			mState = State::DOWNSIDE;
		}
		else if (mMoveState.bWalk)
		{
			mState = State::WALK;
		}
	}

	//void PlayerUpper::ShootSit()
	//{
	//	//OnSit();
	//	mState = State::SIT;
	//}

	/*void PlayerUpper::ShootUpside()
	{
		if (KEY_UP(eKeyCode::UP))
		{
			mState = State::SHOOT;
		}

		if (KEY_UP(eKeyCode::LCTRL))
		{
			mState = State::UPSIDE;
		}
	}
	void PlayerUpper::ShootDownside()
	{
		if (KEY_UP(eKeyCode::DOWN))
		{
			mState = State::SHOOT;
		}
	}*/

	void PlayerUpper::Knife()
	{
		if (KEY_UP(eKeyCode::LCTRL))
		{
			mState = State::IDLE;
		}
	}
	void PlayerUpper::Bomb()
	{
		if (KEY_UP(eKeyCode::LSHIFT))
		{
			mState = State::IDLE;
		}
	}

	void PlayerUpper::Die()
	{
		if (mMoveState.bLeft)
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Die-Left-Pistol", false, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Die-Right-Pistol", false);
		}

		mState = State::REVIVAL;
	}

	void PlayerUpper::Revival()
	{
		//if(mControlState.bAlive)
	}

	void PlayerUpper::OnWalk()
	{
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Walk-Left-Pistol", true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Walk-Right-Pistol", true);
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}
	}

	void PlayerUpper::OnSit()
	{
		Vector2 offset = GetOffset();
		offset.y = 17.0f;
		SetOffset(offset);

		if (mMoveState.bLeft)
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Idle-Left-Pistol", true, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Idle-Right-Pistol", true);
		}
	}

	void PlayerUpper::OnUpside()
	{
		if (mMoveState.bUpside)
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Upside-Left-Pistol", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Upside-Right-Pistol", true);
			}
		}
		else
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}
		}
	}

	void PlayerUpper::OnDownside()
	{
	}

	
}