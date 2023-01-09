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
		, mState(State::IDLE)
		, mArms(eArms::Pistol)
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

		mAnimator = new Animator();
		CreateAnimation();
		mAnimator->Play(L"Idle-Right-Pistol", true);

		AddComponent(mAnimator);

		//mCollider = AddComponent<Collider>();
	}

	void PlayerUpper::Tick()
	{
		GameObject::Tick();

		Player* player = dynamic_cast<Player*>(GetOwner());

		mMoveState = player->GetMoveState();
		mControlState = player->GetControlState();

		if (mArms != player->GetArms())
		{
			mArms = player->GetArms();
			ResetState();
		}
		else
		{
			mArms = player->GetArms();
		}

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
		case ya::PlayerUpper::State::KNIFE_SIT:
			KnifeSit();
			break;
		case ya::PlayerUpper::State::BOMB:
			Bomb();
			break;
		case ya::PlayerUpper::State::BOMB_SIT:
			BombSit();
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
		if (mImage == nullptr)
			mImage = Resources::Load<Image>(L"PlayerUpperPistol", L"..\\Resources\\Image\\Player\\player_upper_pistol.bmp");

		//Pistol
		{
			{ //Upper
				
				{ //Right
					mAnimator->CreateAnimation(L"Idle-Right-Pistol", mImage, Vector2(0.0f, 0.0f), Vector2(31.0f, 29.0f), Vector2(10.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Walk-Right-Pistol", mImage, Vector2(0.0f, 62.0f), Vector2(34.0f, 29.0f), Vector2(8.0f, 0.0f), 12, 0.1f);
					mAnimator->CreateAnimation(L"Jump-Right-Pistol", mImage, Vector2(0.0f, 125.0f), Vector2(33.0f, 26.0f), Vector2(0.0f, -16.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"JumpMove-Right-Pistol", mImage, Vector2(0.0f, 182.0f), Vector2(34.0f, 35.0f), Vector2(0.0f, -24.0f), 6, 0.08f);

					mAnimator->CreateAnimation(L"Knife1-Right-Pistol", mImage, Vector2(0.0f, 318.0f), Vector2(47.0f, 48.0f), Vector2(0.0f, -20.0f), 6, 0.06f);
					mAnimator->CreateAnimation(L"Knife2-Right-Pistol", mImage, Vector2(0.0f, 419.0f), Vector2(50.0f, 33.0f), Vector2(26.0f, -3.0f), 6, 0.06f);
					mAnimator->CreateAnimation(L"Bomb-Right-Pistol", mImage, Vector2(0.0f, 486.0f), Vector2(36.0f, 30.0f), Vector2(12.0f, -2.0f), 6, 0.08f);

					mAnimator->GetCompleteEvent(L"Knife1-Right-Pistol") = std::bind(&PlayerUpper::ResetState, this);
					mAnimator->GetCompleteEvent(L"Knife2-Right-Pistol") = std::bind(&PlayerUpper::ResetState, this);
					mAnimator->GetCompleteEvent(L"Bomb-Right-Pistol") = std::bind(&PlayerUpper::ResetState, this);

					mAnimator->CreateAnimation(L"Shoot-Front-Right-Pistol", mImage, Vector2(0.0f, 256.0f), Vector2(52.0f, 30.0f), Vector2(40.0f, 0.0f), 10, 0.04f);
					mAnimator->GetCompleteEvent(L"Shoot-Front-Right-Pistol") = std::bind(&PlayerUpper::ResetState, this);

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
					mAnimator->CreateAnimation(L"Jump-Left-Pistol", mImage, Vector2(0.0f, 153.0f), Vector2(33.0f, 26.0f), Vector2(10.0f, -16.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"JumpMove-Left-Pistol", mImage, Vector2(0.0f, 219.0f), Vector2(34.0f, 35.0f), Vector2(0.0f, -24.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Knife1-Left-Pistol", mImage, Vector2(0.0f, 368.0f), Vector2(47.0f, 48.0f), Vector2(0.0f, -20.0f), 6, 0.06f);
					mAnimator->CreateAnimation(L"Knife2-Left-Pistol", mImage, Vector2(0.0f, 453.0f), Vector2(50.0f, 33.0f), Vector2(-26.0f, -3.0f), 6, 0.06f);
					mAnimator->CreateAnimation(L"Bomb-Left-Pistol", mImage, Vector2(0.0f, 517.0f), Vector2(36.0f, 30.0f), Vector2(-12.0f, -2.0f), 6, 0.08f);

					mAnimator->GetCompleteEvent(L"Knife1-Left-Pistol") = std::bind(&PlayerUpper::ResetState, this);
					mAnimator->GetCompleteEvent(L"Knife2-Left-Pistol") = std::bind(&PlayerUpper::ResetState, this);
					mAnimator->GetCompleteEvent(L"Bomb-Left-Pistol") = std::bind(&PlayerUpper::ResetState, this);

					mAnimator->CreateAnimation(L"Shoot-Front-Left-Pistol", mImage, Vector2(0.0f, 286.0f), Vector2(52.0f, 30.0f), Vector2(-40.0f, 0.0f), 10, 0.04f);
					mAnimator->GetCompleteEvent(L"Shoot-Front-Left-Pistol") = std::bind(&PlayerUpper::ResetState, this);

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
					mAnimator->CreateAnimation(L"Sit-Knife2-Right-Pistol", mImage, Vector2(0.0f, 1427.0f), Vector2(51.0f, 33.0f), Vector2(0.0f, 0.0f), 6, 0.2f);

					mAnimator->CreateAnimation(L"Revival-Pistol", mImage, Vector2(0.0f, 1756.0f), Vector2(34.0f, 240.0f), Vector2(0.0f, -260.0f), 7, 0.06f);
					mAnimator->GetCompleteEvent(L"Revival-Pistol") = std::bind(&PlayerUpper::OnIdle, this);
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

		{ // °øÅë
			mAnimator->CreateAnimation(L"Die-Right", mImage, Vector2(0.0f, 1674.0f), Vector2(40.0f, 40.0f), Vector2(0.0f, 0.0f), 19, 0.04f);
			mAnimator->CreateAnimation(L"Die-Left", mImage, Vector2(0.0f, 1715.0f), Vector2(40.0f, 40.0f), Vector2(0.0f, 0.0f), 19, 0.04f);
		}

		mImage = Resources::Load<Image>(L"PlayerUpperRiple", L"..\\Resources\\Image\\Player\\player_upper_riple.bmp");

		//Heavy Machinegun
		{
			{ //Upper

				{ //Right
					mAnimator->CreateAnimation(L"Idle-Right-Riple", mImage, Vector2(0.0f, 0.0f), Vector2(40.0f, 29.0f), Vector2(20.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Walk-Right-Riple", mImage, Vector2(0.0f, 60.0f), Vector2(46.0f, 30.0f), Vector2(28.0f, 0.0f), 12, 0.1f);
					mAnimator->CreateAnimation(L"Jump-Right-Riple", mImage, Vector2(0.0f, 127.0f), Vector2(39.0f, 27.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"JumpMove-Right-Riple", mImage, Vector2(0.0f, 188.0f), Vector2(39.0f, 28.0f), Vector2(0.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Shoot-Front-Right-Riple", mImage, Vector2(0.0f, 253.0f), Vector2(62.0f, 28.0f), Vector2(45.0f, 0.0f), 4, 0.04f);
					mAnimator->GetCompleteEvent(L"Shoot-Front-Right-Riple") = std::bind(&PlayerUpper::ResetState, this);

					mAnimator->CreateAnimation(L"Knife1-Right-Riple", mImage, Vector2(0.0f, 318.0f), Vector2(55.0f, 48.0f), Vector2(0.0f, 0.0f), 6, 0.06f);
					mAnimator->CreateAnimation(L"Knife2-Right-Riple", mImage, Vector2(0.0f, 425.0f), Vector2(57.0f, 42.0f), Vector2(0.0f, 0.0f), 6, 0.06f);
					mAnimator->CreateAnimation(L"Bomb-Right-Riple", mImage, Vector2(0.0f, 515.0f), Vector2(42.0f, 29.0f), Vector2(0.0f, 0.0f), 6, 0.1f);

					mAnimator->GetCompleteEvent(L"Knife1-Right-Riple") = std::bind(&PlayerUpper::ResetState, this);
					mAnimator->GetCompleteEvent(L"Knife2-Right-Riple") = std::bind(&PlayerUpper::ResetState, this);
					mAnimator->GetCompleteEvent(L"Bomb-Right-Riple") = std::bind(&PlayerUpper::ResetState, this);

					mAnimator->CreateAnimation(L"Upside-Right-Riple", mImage, Vector2(0.0f, 800.0f), Vector2(26.0f, 49.0f), Vector2(0.0f, 0.0f), 10, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Upside-Right-Riple", mImage, Vector2(0.0f, 904.0f), Vector2(26.0f, 72.0f), Vector2(0.0f, 0.0f), 4, 0.08f);
					mAnimator->CreateAnimation(L"Front-Upside-Right-Riple", mImage, Vector2(0.0f, 578.0f), Vector2(42.0f, 44.0f), Vector2(0.0f, 0.0f), 2, 0.04f);
					mAnimator->CreateAnimation(L"Shoot-Front-Upside-Right-Riple", mImage, Vector2(0.0f, 670.0f), Vector2(58.0f, 63.0f), Vector2(0.0f, 0.0f), 4, 0.1f);

					mAnimator->CreateAnimation(L"Downside-Right-Riple", mImage, Vector2(0.0f, 1274.0f), Vector2(36.0f, 40.0f), Vector2(0.0f, 0.0f), 7, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Downside-Right-Riple", mImage, Vector2(0.0f, 1358.0f), Vector2(36.0f, 63.0f), Vector2(0.0f, 0.0f), 4, 0.1f);
					mAnimator->CreateAnimation(L"Front-Downside-Right-Riple", mImage, Vector2(0.0f, 1054.0f), Vector2(36.0f, 44.0f), Vector2(0.0f, 0.0f), 3, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Front-Downside-Right-Riple", mImage, Vector2(0.0f, 1150.0f), Vector2(54.0f, 60.0f), Vector2(0.0f, 0.0f), 4, 0.1f);

					mAnimator->GetCompleteEvent(L"Front-Upside-Right-Riple") = std::bind(&PlayerUpper::OnUpside, this);
					mAnimator->GetCompleteEvent(L"Front-Downside-Right-Riple") = std::bind(&PlayerUpper::OnDownside, this);
				}

				{ //Left
					mAnimator->CreateAnimation(L"Idle-Left-Riple", mImage, Vector2(0.0f, 30.0f), Vector2(40.0f, 29.0f), Vector2(-20.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Walk-Left-Riple", mImage, Vector2(0.0f, 91.0f), Vector2(46.0f, 30.0f), Vector2(-28.0f, 0.0f), 12, 0.1f);
					mAnimator->CreateAnimation(L"Jump-Left-Riple", mImage, Vector2(0.0f, 155.0f), Vector2(39.0f, 27.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"JumpMove-Left-Riple", mImage, Vector2(0.0f, 218.0f), Vector2(39.0f, 28.0f), Vector2(0.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Shoot-Front-Left-Riple", mImage, Vector2(0.0f, 282.0f), Vector2(62.0f, 28.0f), Vector2(-45.0f, 0.0f), 4, 0.04f);
					mAnimator->GetCompleteEvent(L"Shoot-Front-Left-Riple") = std::bind(&PlayerUpper::ResetState, this);

					mAnimator->CreateAnimation(L"Knife1-Left-Riple", mImage, Vector2(0.0f, 367.0f), Vector2(55.0f, 48.0f), Vector2(0.0f, 0.0f), 6, 0.06f);
					mAnimator->CreateAnimation(L"Knife2-Left-Riple", mImage, Vector2(0.0f, 468.0f), Vector2(57.0f, 42.0f), Vector2(0.0f, 0.0f), 6, 0.06f);
					mAnimator->CreateAnimation(L"Bomb-Left-Riple", mImage, Vector2(0.0f, 545.0f), Vector2(42.0f, 29.0f), Vector2(0.0f, 0.0f), 6, 0.1f);

					mAnimator->GetCompleteEvent(L"Knife1-Left-Riple") = std::bind(&PlayerUpper::ResetState, this);
					mAnimator->GetCompleteEvent(L"Knife2-Left-Riple") = std::bind(&PlayerUpper::ResetState, this);
					mAnimator->GetCompleteEvent(L"Bomb-Left-Riple") = std::bind(&PlayerUpper::ResetState, this);

					mAnimator->CreateAnimation(L"Upside-Left-Riple", mImage, Vector2(0.0f, 850.0f), Vector2(26.0f, 49.0f), Vector2(0.0f, 0.0f), 10, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Upside-Left-Riple", mImage, Vector2(0.0f, 977.0f), Vector2(26.0f, 72.0f), Vector2(0.0f, 0.0f), 4, 0.08f);
					mAnimator->CreateAnimation(L"Front-Upside-Left-Riple", mImage, Vector2(0.0f, 623.0f), Vector2(42.0f, 44.0f), Vector2(0.0f, 0.0f), 2, 0.04f);
					mAnimator->CreateAnimation(L"Shoot-Front-Upside-Left-Riple", mImage, Vector2(0.0f, 734.0f), Vector2(58.0f, 63.0f), Vector2(0.0f, 0.0f), 4, 0.1f);

					mAnimator->CreateAnimation(L"Downside-Left-Riple", mImage, Vector2(0.0f, 1315.0f), Vector2(36.0f, 40.0f), Vector2(0.0f, 0.0f), 7, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Downside-Left-Riple", mImage, Vector2(0.0f, 1422.0f), Vector2(36.0f, 63.0f), Vector2(0.0f, 0.0f), 4, 0.1f);
					mAnimator->CreateAnimation(L"Front-Downside-Left-Riple", mImage, Vector2(0.0f, 1099.0f), Vector2(36.0f, 44.0f), Vector2(0.0f, 0.0f), 3, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Front-Downside-Left-Riple", mImage, Vector2(0.0f, 1211.0f), Vector2(54.0f, 60.0f), Vector2(0.0f, 0.0f), 4, 0.1f);

					mAnimator->GetCompleteEvent(L"Front-Upside-Left-Riple") = std::bind(&PlayerUpper::OnUpside, this);
					mAnimator->GetCompleteEvent(L"Front-Downside-Left-Riple") = std::bind(&PlayerUpper::OnDownside, this);
				}
			}

			{ //Sit
				{ //Right
					mAnimator->CreateAnimation(L"Front-Sit-Right-Riple", mImage, Vector2(0.0f, 1490.0f), Vector2(42.0f, 41.0f), Vector2(0.0f, 0.0f), 3, 0.04f);
					mAnimator->GetCompleteEvent(L"Front-Sit-Right-Riple") = std::bind(&PlayerUpper::OnSit, this);

					mAnimator->CreateAnimation(L"Sit-Turn-Right-Riple", mImage, Vector2(0.0f, 1688.0f), Vector2(26.0f, 26.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Sit-Idle-Right-Riple", mImage, Vector2(0.0f, 1580.0f), Vector2(43.0f, 24.0f), Vector2(12.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Walk-Right-Riple", mImage, Vector2(0.0f, 1189.0f), Vector2(43.0f, 24.0f), Vector2(10.0f, 0.0f), 6, 0.2f);

					mAnimator->CreateAnimation(L"Sit-Shoot-Right-Riple", mImage, Vector2(0.0f, 1745.0f), Vector2(69.0f, 28.0f), Vector2(30.0f, -10.0f), 4, 0.04f);
					mAnimator->CreateAnimation(L"Sit-Bomb-Right-Riple", mImage, Vector2(0.0f, 1806.0f), Vector2(49.0f, 36.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife1-Right-Riple", mImage, Vector2(0.0f, 1884.0f), Vector2(46.0f, 36.0f), Vector2(0.0f, 0.0f), 7, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife2-Right-Riple", mImage, Vector2(0.0f, 1962.0f), Vector2(66.0f, 33.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
				}

				{ //Left
					mAnimator->CreateAnimation(L"Front-Sit-Left-Riple", mImage, Vector2(0.0f, 1532.0f), Vector2(42.0f, 41.0f), Vector2(0.0f, 0.0f), 3, 0.04f);
					mAnimator->GetCompleteEvent(L"Front-Sit-Left-Riple") = std::bind(&PlayerUpper::OnSit, this);

					mAnimator->CreateAnimation(L"Sit-Turn-Left-Riple", mImage, Vector2(0.0f, 1715.0f), Vector2(26.0f, 26.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Sit-Idle-Left-Riple", mImage, Vector2(0.0f, 1605.0f), Vector2(43.0f, 24.0f), Vector2(12.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Walk-Left-Riple", mImage, Vector2(0.0f, 1634.0f), Vector2(43.0f, 24.0f), Vector2(10.0f, 0.0f), 7, 0.2f);

					mAnimator->CreateAnimation(L"Sit-Shoot-Left-Riple", mImage, Vector2(0.0f, 1774.0f), Vector2(69.0f, 28.0f), Vector2(30.0f, -10.0f), 4, 0.04f);
					mAnimator->CreateAnimation(L"Sit-Bomb-Left-Riple", mImage, Vector2(0.0f, 1843.0f), Vector2(49.0f, 36.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife1-Left-Riple", mImage, Vector2(0.0f, 1921.0f), Vector2(46.0f, 36.0f), Vector2(0.0f, 0.0f), 7, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife2-Left-Riple", mImage, Vector2(0.0f, 1996.0f), Vector2(66.0f, 33.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
				}
			}
		}
	}

	void PlayerUpper::Attacked()
	{
		if (mMoveState.bLeft)
			mAnimator->Play(L"Die-Left", false, true);
		else
			mAnimator->Play(L"Die-Right", false);

		mState = State::DIE;
	}

	void PlayerUpper::Idle()
	{
		if (!mControlState.bPlayable)
			return;

		if (mMoveState.bJump)
		{
			mState = State::IDLE;
			ResetState();
			return;
		}

		if (KEY_DOWN(eKeyCode::LEFT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Walk-Left-Pistol", true, true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Walk-Left-Riple", true, true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Walk-Right-Pistol", true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Walk-Right-Riple", true);
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Jump-Left-Riple", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Jump-Right-Pistol", false);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Jump-Right-Riple", false);
			}
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
			return;
		}

		{ // shoot
			if (KEY_DOWN(eKeyCode::LCTRL))
			{
				OnAttack();
			}

			if (KEY_PRESS(eKeyCode::LCTRL))
			{
				if (mMoveState.bKnife)
				{
					mState = State::KNIFE;
					return;
				}
				else
				{
					mState = State::SHOOT;
					return;
				}
			}
		}

		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Bomb-Left-Pistol", false, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Bomb-Left-Riple", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Bomb-Right-Pistol", false);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Bomb-Right-Riple", false);
			}
		}

		if (KEY_PRESS(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}
	}

	void PlayerUpper::Walk()
	{
		if (KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			OnIdle();
			mState = State::IDLE;
			return;
		}

		FrontToUpside();

		{ // shoot
			if (KEY_DOWN(eKeyCode::LCTRL))
			{
				OnAttack();
				return;
			}

			if (KEY_PRESS(eKeyCode::LCTRL))
			{
				if (mMoveState.bKnife)
				{
					mState = State::KNIFE;
					return;
				}
				else
				{
					mState = State::SHOOT;
					return;
				}
			}
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Jump-Left-Pistol", false, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Jump-Left-Riple", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Jump-Right-Pistol", false);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Jump-Right-Riple", false);
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
			OnIdle();
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
			else if (mArms == eArms::HeavyMachinegun)
			{
				if (mMoveState.bLeft)
					mAnimator->Play(L"Downside-Left-Riple", false, true);
				else
					mAnimator->Play(L"Downside-Right-Riple", false);
			}
		}

		if (KEY_PRESS(eKeyCode::LCTRL))
		{
			mState = State::SHOOT;
			return;
		}

		if (KEY_PRESS(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
			return;
		}

		if (KEY_UP(eKeyCode::SPACE))
		{
			mState = State::IDLE;
			return;
		}
	}
	
	void PlayerUpper::WalkJump()
	{
		if (!mMoveState.bJump)
		{
			if (KEY_DOWN(eKeyCode::LEFT))
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Walk-Left-Pistol", true, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Walk-Left-Riple", true, true);
			}
			else if (KEY_DOWN(eKeyCode::RIGHT))
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Walk-Right-Pistol", true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Walk-Right-Riple", true);
			}

			mState = State::WALK;
			return;
		}

		if (KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			mState = State::JUMP;
			return;
		}

		{ // shoot
			if (KEY_DOWN(eKeyCode::LCTRL))
			{
				if (mMoveState.bLeft)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Front-Left-Pistol", false, true);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Shoot-Front-Left-Riple", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Front-Right-Pistol", false);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Shoot-Front-Right-Riple", false);
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
			return;
		}

		if (KEY_UP(eKeyCode::SPACE))
		{
			mState = State::IDLE;
			return;
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Sit-Left-Riple", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Sit-Right-Pistol", false);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Sit-Right-Riple", false);
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
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Sit-Walk-Left-Riple", true, true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Right-Pistol", true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Sit-Walk-Right-Riple", true);
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Idle-Left-Riple", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Idle-Right-Riple", true);
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
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Jump-Left-Riple", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Jump-Right-Pistol", false);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Jump-Right-Riple", false);
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
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Sit-Shoot-Left-Riple", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Sit-Shoot-Right-Pistol", false);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Sit-Shoot-Right-Riple", false);
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Sit-Idle-Left-Riple", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Sit-Idle-Right-Pistol", true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Sit-Idle-Right-Riple", true);
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Idle-Left-Riple", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Idle-Right-Riple", true);
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Upside-Left-Riple", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Upside-Right-Riple", false);
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Upside-Left-Riple", false, false);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Upside-Right-Riple", false, true);
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
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Shoot-Upside-Left-Riple", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Shoot-Upside-Right-Pistol", false);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Shoot-Upside-Right-Riple", false);
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
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Idle-Left-Riple", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Idle-Right-Riple", true);
			}
			mState = State::BOMB;
			return;
		}
	}

	void PlayerUpper::UpsideToFront()
	{
		if (KEY_UP(eKeyCode::UP))
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Upside-Left-Riple", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Upside-Right-Riple", false);
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
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Idle-Left-Riple", true, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Idle-Right-Pistol", true);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Idle-Right-Riple", true);
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
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Front-Downside-Left-Riple", false, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Front-Downside-Right-Pistol", false);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Front-Downside-Right-Riple", false);
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Upside-Left-Riple", false, false);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Front-Upside-Right-Riple", false, true);
			}

			mState = State::DOWNSIDE_TO_FRONT;
			return;
		}

		if (KEY_DOWN(eKeyCode::LEFT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Left-Pistol", true, true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Sit-Walk-Left-Riple", true, true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Right-Pistol", true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Sit-Walk-Right-Riple", true);
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
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Idle-Left-Riple", true, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Idle-Right-Pistol", true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Idle-Right-Riple", true);
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

	void PlayerUpper::Knife()
	{
		if (KEY_UP(eKeyCode::LCTRL))
		{
			mState = State::IDLE;
		}
	}
	void PlayerUpper::KnifeSit()
	{
	}

	void PlayerUpper::Bomb()
	{
		if (KEY_UP(eKeyCode::LSHIFT))
		{
			mState = State::IDLE;
		}
	}

	void PlayerUpper::BombSit()
	{
	}

	void PlayerUpper::Die()
	{
		if (mControlState.bAlive)
		{
			mAnimator->Play(L"Revival-Pistol", true);
			mState = State::REVIVAL;
		}
	}

	void PlayerUpper::Revival()
	{
		mState = State::IDLE;
	}

	void PlayerUpper::OnIdle()
	{
		if (mMoveState.bLeft)
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Idle-Left-Pistol", true, true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Idle-Left-Riple", true, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Idle-Right-Pistol", true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Idle-Right-Riple", true);
		}
	}

	void PlayerUpper::OnWalk()
	{
		if (mMoveState.bLeft)
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Walk-Left-Pistol", true, true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Walk-Left-Riple", true, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Walk-Right-Pistol", true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Walk-Right-Riple", true);
		}
	}

	void PlayerUpper::OnSit()
	{
		if (mMoveState.bLeft)
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Idle-Left-Pistol", true, true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Sit-Idle-Left-Riple", true, true);
		}
		else
		{
			if (mArms == eArms::Pistol)
				mAnimator->Play(L"Sit-Idle-Right-Pistol", true);
			else if (mArms == eArms::HeavyMachinegun)
				mAnimator->Play(L"Sit-Idle-Right-Riple", true);
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
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Upside-Left-Riple", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Upside-Right-Pistol", true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Upside-Right-Riple", true);
			}
		}
		else
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Idle-Left-Riple", true, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Idle-Right-Riple", true);
			}
		}
	}

	void PlayerUpper::OnDownside()
	{
	}

	void PlayerUpper::OnAttack()
	{
		if (mMoveState.bKnife)
		{
			if (mMoveState.bLeft)
			{
				if (ya::math::Random(2) == 0)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Knife1-Left-Pistol", false, true);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Knife1-Left-Riple", false, true);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Knife2-Left-Pistol", false, true);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Knife2-Left-Riple", false, true);
				}
				
			}
			else
			{
				if (ya::math::Random(2) == 0)
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Knife1-Right-Pistol", false);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Knife1-Right-Riple", false);
				}
				else
				{
					if (mArms == eArms::Pistol)
						mAnimator->Play(L"Knife2-Right-Pistol", false);
					else if (mArms == eArms::HeavyMachinegun)
						mAnimator->Play(L"Knife2-Right-Riple", false);
				}
			}
		}
		else
		{
			if (mMoveState.bLeft)
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Shoot-Front-Left-Pistol", false, true);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Shoot-Front-Left-Riple", false, true);
			}
			else
			{
				if (mArms == eArms::Pistol)
					mAnimator->Play(L"Shoot-Front-Right-Pistol", false);
				else if (mArms == eArms::HeavyMachinegun)
					mAnimator->Play(L"Shoot-Front-Right-Riple", false);
			}
		}
	}

	void PlayerUpper::OnDie()
	{
	}

	void PlayerUpper::ResetState()
	{
		if (mMoveState.bWalk)
			OnWalk();
		else if (mMoveState.bSit)
			OnSit();
		else
			OnIdle();
	}

	void PlayerUpper::PickupArms()
	{
	}

	
}