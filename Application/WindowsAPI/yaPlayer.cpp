#include "yaPlayer.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaTime.h"
#include "yaInput.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

#include "yaUIManager.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaPlayerUpper.h"
#include "yaPlayerLower.h"
#include "yaBackpack.h"
#include "yaMissile.h"
#include "yaRock.h"
#include "yaEffect.h"

namespace ya
{
	Player::Player()
		: mSpeed(200.0f)
		, mbLeft(false)
		, mbJump(false)
		, mbSit(false)
		, mbFall(true)
		, mbUpside(false)
		, mbDownside(false)
		, mUpper(nullptr)
		, mLower(nullptr)
	{
		SetName(L"Player");
		SetPos({ 40.0f, 60.0f });
		SetScale({ 2.6f, 2.6f });
		SetSize({ 24.0f, 36.0f });

		Initialize();
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		PlayerLower* lower = new PlayerLower();
		AddChild(lower);
		lower->Initialize();
		
		PlayerUpper* upper = new PlayerUpper();
		AddChild(upper);
		upper->Initialize();

		/*Collider* collider = new Collider();
		collider->SetSize(GetSize());
		collider->SetScale(GetScale());
		collider->SetOffset({0.0f, 0.0f});
		AddComponent(collider);*/

		AddComponent(new Rigidbody());
	}

	void Player::Tick()
	{
		GameObject::Tick();

		Rigidbody* rigidbody = GetComponent<Rigidbody>();;

		switch (mState)
		{
		case ya::Player::State::IDLE:
			Idle();
			break;
		case ya::Player::State::WALK:
			Walk();
			break;
		case ya::Player::State::JUMP:
			Jump(rigidbody);
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
		case ya::Player::State::SHOOT_FRONT_UPSIDE:
			break;
		case ya::Player::State::SHOOT_UPSIDE:
			ShootUpside();
			break;
		case ya::Player::State::SHOOT_DOWNSIDE:
			ShootDownside();
			break;
		case ya::Player::State::KNIFE:
			Knife();
			break;
		case ya::Player::State::BOMB:
			Bomb();
			break;
		default:
			break;
		}

		

		/*if (KEY_DOWN(eKeyCode::I))
		{
			Backpack* backPack = new Backpack();
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(backPack, eColliderLayer::Backpack);
		}*/

	}

	void Player::Render(HDC hdc)
	{
		wchar_t szFloat[50] = {};
		std::wstring str = std::to_wstring(GetPos().x) + L", " + std::to_wstring(GetPos().y);
		swprintf_s(szFloat, 50, str.c_str());
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 10, szFloat, strLen);

		GameObject::Render(hdc); /// 자식이 먼저그려져양함
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

	void Player::ShootArms()
	{
		Missile* missile = new Missile();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerScale = GetScale() / 2.0f;

		Vector2 missileScale = missile->GetScale();

		missile->SetPos(playerPos + playerScale - (missileScale / 2.0f));
	}

	void Player::Idle()
	{
		mbJump = false;

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
		}

		if (KEY_PRESS(eKeyCode::UP))
		{
			mState = State::UPSIDE;
			
		}
		if (KEY_PRESS(eKeyCode::DOWN))
		{
			mState = State::SIT;
		}

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			mState = State::SHOOT;
		}
	}

	void Player::Walk()
	{
		Vector2 pos = GetPos();

		if (KEY_PRESS(eKeyCode::SPACE))
		{
			mState = State::JUMP;
		}

		if (KEY_PRESS(eKeyCode::LEFT))
		{
			mbLeft = true;
			pos.x -= mSpeed * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::RIGHT))
		{
			mbLeft = false;
			pos.x += mSpeed * Time::DeltaTime();
		}

		SetPos(pos);

		if (KEY_UP(eKeyCode::LEFT)
			|| KEY_UP(eKeyCode::RIGHT))
		{
			mState = State::IDLE;
		}
	}

	void Player::Jump(Rigidbody* rigidbody)
	{
		if (!mbJump)
		{
			Vector2 velocity = rigidbody->GetVelocity();
			velocity.y = -560.0f;
			rigidbody->SetVelocity(velocity);
			rigidbody->SetGround(false);
		}

		mbFall = (rigidbody->GetVelocity().y > 0);

		if (rigidbody->isGround())
		{
			mbJump = false;
			mState = State::IDLE;
			return;
		}

		mbJump = true;

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
		mbSit = true;

		if (KEY_UP(eKeyCode::DOWN))
		{
			mbSit = false;
			mState = State::IDLE;
			return;
		}

		if (KEY_PRESS(eKeyCode::LEFT) || KEY_PRESS(eKeyCode::RIGHT))
		{
			mState = State::WALK;
			return;
		}
	}

	void Player::Upside()
	{
		mbUpside = true;

		if (KEY_UP(eKeyCode::UP))
		{
			mbUpside = false;
			mState = State::IDLE;
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			mState = State::SHOOT_UPSIDE;
		}
	}

	void Player::Downside()
	{
		mbDownside = true;

		if(!mbJump)
		{
			mbDownside = false;
			mState = State::IDLE;
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			mState = State::SHOOT_DOWNSIDE;
		}
	}

	void Player::Shoot()
	{
		ShootArms();

		mState = State::IDLE;
	}

	void Player::ShootFrontUpside()
	{
	}

	void Player::ShootUpside()
	{
		ShootArms();

		mState = State::UPSIDE;
	}

	void Player::ShootDownside()
	{
		ShootArms();

		mState = State::DOWNSIDE;
	}

	void Player::Knife()
	{
		if (KEY_UP(eKeyCode::LCTRL))
		{
			mState = State::IDLE;
		}
	}

	void Player::Bomb()
	{
		if (KEY_UP(eKeyCode::LSHIFT))
		{
			mState = State::IDLE;
		}
	}

	void Player::WalkComplete()
	{
		/*Effect* effect = new Effect();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(effect, eColliderLayer::Player_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerScale = GetScale();
		Vector2 footprintScale = effect->GetScale();

		effect->SetPos((playerPos + playerScale) - (footprintScale / 2.0f));*/
	}
}