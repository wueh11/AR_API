#include "yaPlayerUpper.h"

#include "yaResources.h"
#include "yaInput.h"
#include "yaImage.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

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

		Collider* collider = new Collider();
		collider->SetSize(GetSize());
		collider->SetScale(GetScale());
		collider->SetOffset({ 0.0f, 0.0f });
		//AddComponent(collider);
	}

	void PlayerUpper::Tick()
	{
		GameObject::Tick();

		Player* player = dynamic_cast<Player*>(GetOwner());

		Vector2 pos = player->GetPos() + GetOffset();
		eArms arms = player->GetArms();

		bool bLeft = player->IsLeft();
		bool bJump = player->IsJumping();
		bool bSit = player->IsSitting();
		bool bUpside = player->IsUpside();
		bool bDownside = player->IsDownside();

		switch (mState)
		{
		case ya::PlayerUpper::State::IDLE:
			Idle(arms, bLeft);
			break;
		case ya::PlayerUpper::State::WALK:
			Walk(arms, bLeft);
			break;
		case ya::PlayerUpper::State::JUMP:
			Jump(arms, bLeft, bJump);
			break;
		case ya::PlayerUpper::State::WALKJUMP:
			WalkJump(arms, bLeft, bJump);
			break;
		case ya::PlayerUpper::State::FRONT_TO_UPSIDE:
			FrontToUpside(arms, bLeft);
			break;
		case ya::PlayerUpper::State::UPSIDE:
			Upside(arms, bLeft);
			break;
		case ya::PlayerUpper::State::UPSIDE_TO_FRONT:
			UpsideToFront(arms, bLeft);
			break;
		case ya::PlayerUpper::State::FRONT_TO_DOWNSIDE:
			FrontToDownside(arms, bLeft);
			break;
		case ya::PlayerUpper::State::DOWNSIDE:
			Downside(arms, bLeft);
			break;
		case ya::PlayerUpper::State::DOWNSIDE_TO_FRONT:
			DownsideToFront(arms, bLeft);
			break;
		case ya::PlayerUpper::State::SHOOT:
			Shoot(arms, bLeft);
			break;
		case ya::PlayerUpper::State::SHOOT_UPSIDE:
			ShootUpside(arms, bLeft);
			break;
		case ya::PlayerUpper::State::SHOOT_DOWNSIDE:
			ShootDownside(arms, bLeft);
			break;
		case ya::PlayerUpper::State::KNIFE:
			Knife(arms, bLeft);
			break;
		case ya::PlayerUpper::State::BOMB:
			Bomb(arms, bLeft);
			break;
		default:
			break;
		}

		/*if (KEY_DOWN(eKeyCode::UP))
		{
			if (bLeft)
			{
				mAnimator->Play(L"Front-Upside-Left-Pistol", false, true);
			}
			else
			{
				mAnimator->Play(L"Front-Upside-Right-Pistol", false);
			}
			
		}
		else if (KEY_DOWN(eKeyCode::DOWN))
		{
			if (bLeft)
			{
				mAnimator->Play(L"Front-Downside-Left-Pistol", false, true);
			}
			else
			{
				mAnimator->Play(L"Front-Downside-Right-Pistol", false);
			}
		}
		
		else if (KEY_DOWN(eKeyCode::LCTRL))
		{
			if(bJump)

			if (bLeft)
			{
				mAnimator->Play(L"Front-Downside-Left-Pistol", false, true);
			}
			else
			{
				mAnimator->Play(L"Front-Downside-Right-Pistol", false);
			}
		}

		

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			mAnimator->Play(L"Jump-Right-Pistol", false);
		}
		
		if (KEY_UP(eKeyCode::UP))
		{
			mAnimator->Play(L"Idle-Right-Pistol", true);
		}
		if (KEY_UP(eKeyCode::DOWN))
		{
			mAnimator->Play(L"Idle-Right-Pistol", true);
		}
		if (KEY_UP(eKeyCode::LEFT))
		{
			mAnimator->Play(L"Idle-Right-Pistol", true);
		}
		if (KEY_UP(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"Idle-Right-Pistol", true);
		}*/

		SetPos(pos);
	}

	void PlayerUpper::Render(HDC hdc)
	{
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
					mAnimator->CreateAnimation(L"Jump-Right-Pistol", mImage, Vector2(0.0f, 60.0f), Vector2(64.0f, 28.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"JumpMove-Right-Pistol", mImage, Vector2(0.0f, 182.0f), Vector2(34.0f, 35.0f), Vector2(2.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Knife1-Right-Pistol", mImage, Vector2(0.0f, 318.0f), Vector2(43.0f, 48.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"Knife2-Right-Pistol", mImage, Vector2(0.0f, 419.0f), Vector2(50.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"Bomb-Right-Pistol", mImage, Vector2(0.0f, 486.0f), Vector2(30.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Shoot-Front-Right-Pistol", mImage, Vector2(0.0f, 256.0f), Vector2(52.0f, 30.0f), Vector2(2.0f, 0.0f), 10, 0.1f);

					mAnimator->CreateAnimation(L"Upside-Right-Pistol", mImage, Vector2(0.0f, 548.0f), Vector2(34.0f, 26.0f), Vector2(10.0f, -12.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Front-Upside-Right-Pistol", mImage, Vector2(0.0f, 606.0f), Vector2(36.0f, 32.0f), Vector2(12.0f, -18.0f), 2, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Upside-Right-Pistol", mImage, Vector2(0.0f, 672.0f), Vector2(29.0f, 66.0f), Vector2(0.0f, 0.0f), 10, 0.1f);
					
					//mAnimator->GetEndEvent(L"Front-Upside-Right-Pistol") = std::bind(&PlayerUpper::Upside), this);

					mAnimator->CreateAnimation(L"Downside-Right-Pistol", mImage, Vector2(54.0f, 808.0f), Vector2(26.0f, 30.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Front-Downside-Right-Pistol", mImage, Vector2(0.0f, 808.0f), Vector2(26.0f, 30.0f), Vector2(0.0f, 0.0f), 3, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Downside-Right-Pistol", mImage, Vector2(0.0f, 888.0f), Vector2(25.0f, 52.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
				}

				{ //Left
					mAnimator->CreateAnimation(L"Idle-Left-Pistol", mImage, Vector2(0.0f, 30.0f), Vector2(31.0f, 29.0f), Vector2(-10.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Walk-Left-Pistol", mImage, Vector2(0.0f, 93.0f), Vector2(34.0f, 29.0f), Vector2(-8.0f, 0.0f), 12, 0.1f);
					mAnimator->CreateAnimation(L"Jump-Left-Pistol", mImage, Vector2(0.0f, 152.0f), Vector2(64.0f, 28.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"JumpMove-Left-Pistol", mImage, Vector2(0.0f, 219.0f), Vector2(34.0f, 35.0f), Vector2(2.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Knife1-Left-Pistol", mImage, Vector2(0.0f, 368.0f), Vector2(43.0f, 48.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"Knife2-Left-Pistol", mImage, Vector2(0.0f, 453.0f), Vector2(50.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
					mAnimator->CreateAnimation(L"Bomb-Left-Pistol", mImage, Vector2(0.0f, 517.0f), Vector2(30.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);

					mAnimator->CreateAnimation(L"Shoot-Front-Left-Pistol", mImage, Vector2(0.0f, 286.0f), Vector2(52.0f, 30.0f), Vector2(2.0f, 0.0f), 10, 0.1f);

					mAnimator->CreateAnimation(L"Upside-Left-Pistol", mImage, Vector2(0.0f, 576.0f), Vector2(34.0f, 26.0f), Vector2(-6.0f, -12.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Front-Upside-Left-Pistol", mImage, Vector2(0.0f, 639.0f), Vector2(36.0f, 32.0f), Vector2(-12.0f, -18.0f), 2, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Upside-Left-Pistol", mImage, Vector2(0.0f, 739.0f), Vector2(29.0f, 66.0f), Vector2(0.0f, 0.0f), 10, 0.1f);

					mAnimator->CreateAnimation(L"Downside-Left-Pistol", mImage, Vector2(54.0f, 848.0f), Vector2(26.0f, 30.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Front-Downside-Left-Pistol", mImage, Vector2(0.0f, 48.0f), Vector2(26.0f, 30.0f), Vector2(0.0f, 0.0f), 3, 0.1f);
					mAnimator->CreateAnimation(L"Shoot-Downside-Left-Pistol", mImage, Vector2(0.0f, 944.0f), Vector2(25.0f, 52.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
				}
			}
			
			{ //Sit
				{ //Right
					mAnimator->CreateAnimation(L"Front-Sit-Right-Pistol", mImage, Vector2(0.0f, 999.0f), Vector2(34.0f, 41.0f), Vector2(0.0f, 0.0f), 3, 0.1f);
					mAnimator->CreateAnimation(L"Sit-Turn-Right-Pistol", mImage, Vector2(0.0f, 1085.0f), Vector2(23.0f, 25.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Sit-Idle-Right-Pistol", mImage, Vector2(0.0f, 1139.0f), Vector2(39.0f, 24.0f), Vector2(0.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Walk-Right-Pistol", mImage, Vector2(0.0f, 1189.0f), Vector2(39.0f, 24.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Shoot-Right-Pistol", mImage, Vector2(0.0f, 1241.0f), Vector2(55.0f, 27.0f), Vector2(0.0f, 0.0f), 10, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Bomb-Right-Pistol", mImage, Vector2(0.0f, 1299.0f), Vector2(43.0f, 28.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife1-Right-Pistol", mImage, Vector2(0.0f, 1357.0f), Vector2(43.0f, 34.0f), Vector2(0.0f, 0.0f), 7, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife2-Right-Pistol", mImage, Vector2(0.0f, 1427.0f), Vector2(51.0f, 33.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
				}

				{ //Left
					mAnimator->CreateAnimation(L"Front-Sit-Left-Pistol", mImage, Vector2(0.0f, 1042.0f), Vector2(34.0f, 41.0f), Vector2(0.0f, 0.0f), 3, 0.1f);
					mAnimator->CreateAnimation(L"Sit-Turn-Left-Pistol", mImage, Vector2(0.0f, 1112.0f), Vector2(23.0f, 25.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
					mAnimator->CreateAnimation(L"Sit-Idle-Left-Pistol", mImage, Vector2(0.0f, 1164.0f), Vector2(39.0f, 24.0f), Vector2(0.0f, 0.0f), 4, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Walk-Left-Pistol", mImage, Vector2(0.0f, 1214.0f), Vector2(39.0f, 24.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Shoot-Left-Pistol", mImage, Vector2(0.0f, 1270.0f), Vector2(55.0f, 27.0f), Vector2(0.0f, 0.0f), 10, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Bomb-Left-Pistol", mImage, Vector2(0.0f, 1328.0f), Vector2(43.0f, 28.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife1-Left-Pistol", mImage, Vector2(0.0f, 1392.0f), Vector2(43.0f, 34.0f), Vector2(0.0f, 0.0f), 7, 0.2f);
					mAnimator->CreateAnimation(L"Sit-Knife2-Left-Pistol", mImage, Vector2(0.0f, 1461.0f), Vector2(51.0f, 33.0f), Vector2(0.0f, 0.0f), 6, 0.2f);
				}
			}
		}

		//Heavy Machinegun
		{

		}

		//Flamegun
		{

		}
	}

	void PlayerUpper::Idle(eArms arms, bool bLeft)
	{
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Walk-Left-Pistol", true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Walk-Right-Pistol", true);
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}

		if (KEY_DOWN(eKeyCode::UP))
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, true);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false);
			}
		}

		if (KEY_PRESS(eKeyCode::UP))
		{
			mState = State::FRONT_TO_UPSIDE;
			return;
		}

		if (KEY_DOWN(eKeyCode::DOWN))
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Sit-Left-Pistol", true, true);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Sit-Right-Pistol", true);
			}
		}

		if (KEY_PRESS(eKeyCode::DOWN))
		{
			mState = State::FRONT_TO_DOWNSIDE;
			return;
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
			return;
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
	}
	void PlayerUpper::Walk(eArms arms, bool bLeft)
	{
		if (KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}

			mState = State::IDLE;
			return;
		}

		if (KEY_DOWN(eKeyCode::UP))
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, true);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false);
			}
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::WALKJUMP;
			return;
		}


		if (KEY_PRESS(eKeyCode::UP))
		{
			mState = State::FRONT_TO_UPSIDE;
		}

		if (KEY_PRESS(eKeyCode::DOWN))
		{
			mState = State::FRONT_TO_DOWNSIDE;
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
	void PlayerUpper::Jump(eArms arms, bool bLeft, bool bJump)
	{
		if (!bJump)
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}

			mState = State::IDLE;
			return;
		}

		if (KEY_DOWN(eKeyCode::DOWN))
		{
			if (arms == eArms::Pistol)
			{
				if (bLeft)
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
	void PlayerUpper::WalkJump(eArms arms, bool bLeft, bool bJump)
	{
		if (!bJump)
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}

			mState = State::IDLE;
			return;
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
	void PlayerUpper::FrontToUpside(eArms arms, bool bLeft)
	{
		if (KEY_PRESS(eKeyCode::LCTRL))
		{
			mState = State::SHOOT_UPSIDE;
			return;
		}

		if (KEY_UP(eKeyCode::UP))
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}
			mState = State::IDLE;
			return;
		}
		
		if (bLeft)
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Upside-Left-Pistol", true, true);
		}
		else
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Upside-Right-Pistol", true);
		}

		mState = State::UPSIDE;
	}
	void PlayerUpper::Upside(eArms arms, bool bLeft)
	{
		if (KEY_UP(eKeyCode::UP))
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, false);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false, true);
			}

			mState = State::UPSIDE_TO_FRONT;
			return;
		}

		/*if (KEY_PRESS(eKeyCode::LCTRL))
		{
			mState = State::SHOOT_UPSIDE;
		}

		if (KEY_PRESS(eKeyCode::LCTRL))
		{
			mState = State::SHOOT;
		}

		if (KEY_PRESS(eKeyCode::LSHIFT))
		{
			mState = State::BOMB;
		}*/
	}

	void PlayerUpper::UpsideToFront(eArms arms, bool bLeft)
	{
		if (bLeft)
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Idle-Left-Pistol", true, true);
		}
		else
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Idle-Right-Pistol", true);
		}

		mState = State::IDLE;
	}

	void PlayerUpper::FrontToDownside(eArms arms, bool bLeft)
	{
		if (KEY_PRESS(eKeyCode::LCTRL))
		{
			mState = State::SHOOT;
			return;
		}

		if (KEY_UP(eKeyCode::DOWN))
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Left-Pistol", true, true);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Idle-Right-Pistol", true);
			}
			mState = State::IDLE;
			return;
		}

		if (bLeft)
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Sit-Idle-Left-Pistol", true, true);
		}
		else
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Sit-Idle-Right-Pistol", true);
		}

		mState = State::DOWNSIDE;
	}

	void PlayerUpper::Downside(eArms arms, bool bLeft)
	{
		if (KEY_UP(eKeyCode::DOWN))
		{
			if (bLeft)
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Left-Pistol", false, false);
			}
			else
			{
				if (arms == eArms::Pistol)
					mAnimator->Play(L"Front-Upside-Right-Pistol", false, true);
			}

			mState = State::DOWNSIDE_TO_FRONT;
			return;
		}

		if (KEY_DOWN(eKeyCode::LEFT))
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Left-Pistol", true, true);
		}
		else if (KEY_DOWN(eKeyCode::RIGHT))
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Sit-Walk-Right-Pistol", true);
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}
	}
	void PlayerUpper::DownsideToFront(eArms arms, bool bLeft)
	{
		if (bLeft)
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Idle-Left-Pistol", true, true);
		}
		else
		{
			if (arms == eArms::Pistol)
				mAnimator->Play(L"Idle-Right-Pistol", true);
		}

		mState = State::IDLE;
	}
	void PlayerUpper::Shoot(eArms arms, bool bLeft)
	{
		if (KEY_UP(eKeyCode::LCTRL))
		{
			mState = State::IDLE;
		}
	}
	void PlayerUpper::ShootUpside(eArms arms, bool bLeft)
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
	void PlayerUpper::ShootDownside(eArms arms, bool bLeft)
	{
		if (KEY_UP(eKeyCode::DOWN))
		{
			mState = State::SHOOT;
		}
	}
	void PlayerUpper::Knife(eArms arms, bool bLeft)
	{
		if (KEY_UP(eKeyCode::LCTRL))
		{
			mState = State::IDLE;
		}
	}
	void PlayerUpper::Bomb(eArms arms, bool bLeft)
	{
		if (KEY_UP(eKeyCode::LSHIFT))
		{
			mState = State::IDLE;
		}
	}
}