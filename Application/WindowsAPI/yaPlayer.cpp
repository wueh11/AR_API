#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaImage.h"
#include "yaResources.h"

#include "yaMissile.h"
#include "yaRock.h"

#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	Player::Player()
		: mSpeed(200.0f)
	{
		SetPos({ 500.0f, 400.0f });
		SetScale({ 2.0f, 2.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\Player.bmp");
		}

		AddComponent(new Animator());
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
			playScene->AddGameObject(missile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.0f;

			Vector2 missileScale = missile->GetScale();

			missile->SetPos(playerPos + playerScale - (missileScale / 2.0f));
		}
		
		if (rand() % 2000 > 1990)
		{
			Rock* rock = new Rock();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(rock);
		}

		SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		Brush brush(hdc, blueBrush); /// 지역변수가 해제될대 자동으로 DeleteObject 수행

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
			, rect.x, rect.y, mImage->GetDC()  ///dc, 시작위치, 이미지 크기, 복사할dc
			, 0, 0, mImage->GetWidth(), mImage->GetHeight() /// 이미지의 시작, 끝부분 좌표(자르기)
			, RGB(255, 255, 255)); ///crTransparent의 인자를 제외시키고 출력한다.(투명처리)

		GameObject::Render(hdc); /// 자식이 먼저그려져양함
	}
}