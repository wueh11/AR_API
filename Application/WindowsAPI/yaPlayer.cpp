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
		, mLeft(false)
		, mUpper(nullptr)
		, mLower(nullptr)
	{
		SetName(L"Player");
		SetPos({ 40.0f, 60.0f });
		SetScale({ 3.0f, 3.0f });
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

		Vector2 pos = GetPos();

		//if (KEY_PRESS(eKeyCode::W))
		//{
		//	// 위방향봄
		//}
		//if (KEY_PRESS(eKeyCode::S))
		//{
		//	// 아래방향봄
		//}
		if (KEY_PRESS(eKeyCode::A))
		{
			mLeft = true;
			pos.x -= mSpeed * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::D))
		{
			mLeft = false;
			pos.x += mSpeed * Time::DeltaTime();
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();

			//if (rigidbody->isGround())
			{
				velocity.y = -500.0f;
				rigidbody->SetVelocity(velocity);

				rigidbody->SetGround(false);
			}

			//mAnimator[0]->Play(L"JumpPistolRight", false);
			//mAnimator[1]->Play(L"JumpPistolRight", false);
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			Missile* missile = new Missile();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.0f;

			Vector2 missileScale = missile->GetScale();

			missile->SetPos(playerPos + playerScale - (missileScale / 2.0f));

		}

		/*if (KEY_DOWN(eKeyCode::I))
		{
			Backpack* backPack = new Backpack();
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(backPack, eColliderLayer::Backpack);
		}*/

		SetPos(pos);
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