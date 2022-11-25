#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaImage.h"
#include "yaResources.h"

#include "yaMissile.h"
#include "yaRock.h"
#include "yaBackpack.h"
#include "yaEffect.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"
#include "yaUIManager.h"

namespace ya
{
	Player::Player()
		: mSpeed(200.0f)
	{
		SetName(L"Player");
		SetPos({ 40.0f, 60.0f });
		SetScale({ 1.0f, 1.0f });
		SetSize({ 40.0f, 60.0f });

		Initialize();
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		//Lower
		{
			if (mImage[1] == nullptr)
				mImage[1] = Resources::Load<Image>(L"PlayerLower", L"..\\Resources\\Image\\Player\\player1.bmp");

			mAnimator[1] = new Animator();
			mAnimator[1]->SetOffset({ 0.0f, 30.0f });
			mAnimator[1]->CreateAnimation(L"Idle", mImage[1]
				, Vector2(0.0f, 2900.0f), Vector2(42.0f, 32.0f)
				, Vector2(.0f, .0f), 1, 0.2f);

			mAnimator[1]->Play(L"Idle", true);

			AddComponent(mAnimator[1]);
		}

		//Upper
		{
			if (mImage[0] == nullptr)
				mImage[0] = Resources::Load<Image>(L"PlayerUpper", L"..\\Resources\\Image\\Player\\player1.bmp");

			mAnimator[0] = new Animator();
			mAnimator[0]->SetOffset({ 8.0f, 0.0f });
			mAnimator[0]->CreateAnimation(L"Idle", mImage[0]
				, Vector2(0.0f, 480.0f), Vector2(62.0f, 58.0f)
				, Vector2(0.0f, 0.0f), 4, 0.2f);

			mAnimator[0]->Play(L"Idle", true);

			AddComponent(mAnimator[0]);
		}

		Collider* collider = new Collider();
		collider->SetSize(GetSize());
		collider->SetOffset({0.0f, 10.0f});
		AddComponent(collider);
		AddComponent(new Rigidbody());
	}

	void Player::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();
		if (KEY_PRESS(eKeyCode::W))
		{
			//GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -mSpeed));
		}
		if (KEY_PRESS(eKeyCode::S))
		{
			//GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, mSpeed));
		}
		if (KEY_PRESS(eKeyCode::A))
		{
			pos.x -= 120.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(-mSpeed, 0.0f));
		}
		if (KEY_PRESS(eKeyCode::D))
		{
			pos.x += 120.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(mSpeed, 0.0f));
		}

		/*if (KEY_DOWN(eKeyCode::W))
		{
			mAnimator[0]->Play(L"MoveUp", true);
			mAnimator[1]->Play(L"MoveUp", true);
		}
		if (KEY_DOWN(eKeyCode::S))
		{
			mAnimator[0]->Play(L"MoveDown", true);
			mAnimator[1]->Play(L"MoveDown", true);
		}
		if (KEY_DOWN(eKeyCode::A))
		{
			mAnimator[0]->Play(L"MoveLeft", true);
			mAnimator[1]->Play(L"MoveLeft", true);
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			mAnimator[0]->Play(L"MoveRight", true);
			mAnimator[1]->Play(L"MoveRight", true);
		}*/

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
		
		if (KEY_DOWN(eKeyCode::I))
		{
			Backpack* backPack = new Backpack();
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(backPack, eColliderLayer::Backpack);
		}

		SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		/*Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = pos.x - mImage[0]->GetWidth() * (scale.x / 2.0f);
		finalPos.y = pos.y - mImage[0]->GetHeight() * (scale.y / 2.0f);

		TransparentBlt(hdc, finalPos.x, finalPos.y + 40.0f
			, rect.x, rect.y, mImage[1]->GetDC()
			, 0, 0, mImage[1]->GetWidth(), mImage[1]->GetHeight() 
			, RGB(255, 0, 255)); */

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
		Effect* effect = new Effect();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(effect, eColliderLayer::Player_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerScale = GetScale();
		Vector2 footprintScale = effect->GetScale();

		effect->SetPos((playerPos + playerScale) - (footprintScale / 2.0f));
	}

	void Player::Walking()
	{
	}
}