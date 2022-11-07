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

namespace ya
{
	Player::Player()
		: mSpeed(200.0f)
	{
		SetName(L"Player");
		SetPos({ 500.0f, 400.0f });
		SetScale({ 2.0f, 2.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\Player.bmp");
		}
		SetSize({ (float)(mImage->GetWidth() * GetScale().x), (float)(mImage->GetHeight() * GetScale().y) });

		mAnimator = new Animator();

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 3, 0.1f);

		mAnimator->Play(L"Idle", true);

		AddComponent(mAnimator);
		AddComponent(new Collider());
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
			pos.y -= mSpeed * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::S))
		{
			pos.y += mSpeed * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::A))
		{
			pos.x -= mSpeed * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::D))
		{
			pos.x += mSpeed * Time::DeltaTime();
		}

		if (KEY_DOWN(eKeyCode::SPACE))
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

		/*if (rand() % 2000 > 1990)
		{
			Rock* rock = new Rock();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(rock, eColliderLayer::Monster_Projecttile);
		}*/

		SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		Brush brush(hdc, blueBrush); /// ���������� �����ɴ� �ڵ����� DeleteObject ����

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		Pen pen(hdc, redPen);

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		
		//Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
		//BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetDC(), 0, 0, SRCCOPY);

		Vector2 finalPos;
		finalPos.x = pos.x - mImage->GetWidth() * (scale.x / 2.0f);
		finalPos.y = pos.y - mImage->GetHeight() * (scale.y / 2.0f);

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		TransparentBlt(hdc, finalPos.x, finalPos.y
			, rect.x, rect.y, mImage->GetDC()  ///dc, ������ġ, �̹��� ũ��, ������dc
			, 0, 0, mImage->GetWidth(), mImage->GetHeight() /// �̹����� ����, ���κ� ��ǥ(�ڸ���)
			, RGB(255, 255, 255)); ///crTransparent�� ���ڸ� ���ܽ�Ű�� ����Ѵ�.(����ó��)

		GameObject::Render(hdc); /// �ڽ��� �����׷�������
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