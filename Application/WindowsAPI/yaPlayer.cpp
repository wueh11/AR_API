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
		SetPos({ 500.0f, 400.0f });
		SetScale({ 2.0f, 2.0f });
		SetSize({ 100.0f, 100.0f });
		
		//Upper
		{
			if (mImage[0] == nullptr)
				mImage[0] = Resources::Load<Image>(L"PlayerUpper", L"..\\Resources\\Image\\link.bmp");
		
			mAnimator[0] = new Animator();
			mAnimator[0]->CreateAnimation(L"Idle", mImage[0]
				, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f)
				, Vector2(5.0f, -20.0f), 3, 0.1f);

			mAnimator[0]->Play(L"Idle", true);

			AddComponent(mAnimator[0]);
		}

		//Lower
		{
			if (mImage[1] == nullptr)
				mImage[1] = Resources::Load<Image>(L"PlayerLower", L"..\\Resources\\Image\\link.bmp");

			mAnimator[1] = new Animator();
			mAnimator[1]->SetOffset({ 0.0f, 40.0f });
			mAnimator[1]->CreateAnimation(L"Idle", mImage[1]
				, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f)
				, Vector2(5.0f, -20.0f), 3, 0.1f);

			mAnimator[1]->Play(L"Idle", true);

			AddComponent(mAnimator[1]);
		}

		AddComponent(new Collider());
		AddComponent(new Rigidbody());
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
	}

	void Player::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();
		if (KEY_PRESS(eKeyCode::W))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -mSpeed));
		}
		if (KEY_PRESS(eKeyCode::S))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, mSpeed));
		}
		if (KEY_PRESS(eKeyCode::A))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(-mSpeed, 0.0f));
		}
		if (KEY_PRESS(eKeyCode::D))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(mSpeed, 0.0f));
		}

		if (KEY_DOWN(eKeyCode::W))
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
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();

			if (rigidbody->isGround())
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
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = pos.x - mImage[0]->GetWidth() * (scale.x / 2.0f);
		finalPos.y = pos.y - mImage[0]->GetHeight() * (scale.y / 2.0f);

		/*Vector2 rect;
		rect.x = mImage[0]->GetWidth() * scale.x;
		rect.y = mImage[0]->GetHeight() * scale.y;

		TransparentBlt(hdc, finalPos.x, finalPos.y
			, rect.x, rect.y, mImage[0]->GetDC()  ///dc, 시작위치, 이미지 크기, 복사할dc
			, 0, 0, mImage[0]->GetWidth(), mImage[0]->GetHeight() /// 이미지의 시작, 끝부분 좌표(자르기)
			, RGB(255, 0, 255)); ///crTransparent의 인자를 제외시키고 출력한다.(투명처리)

		TransparentBlt(hdc, finalPos.x, finalPos.y + 40.0f
			, rect.x, rect.y, mImage[1]->GetDC()
			, 0, 0, mImage[1]->GetWidth(), mImage[1]->GetHeight() 
			, RGB(255, 0, 255)); */

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