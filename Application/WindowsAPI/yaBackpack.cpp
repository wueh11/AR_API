#include "yaBackpack.h"

#include "yaTime.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaImage.h"
#include "yaResources.h"


ya::Backpack::Backpack()
	: mSpeed(1.0f)
	, mImage(nullptr)
	, mbView(false)
{
	SetName(L"BackPack");
	SetPos({ (1600 / 2) - (GetPos().x / 2), (900 / 2) - (GetPos().y / 2) });
	SetScale({ 3.0f, 3.0f });

	if (mImage == nullptr)
	{
		mImage = Resources::Load<Image>(L"BackPack", L"..\\Resources\\Image\\BackPack.bmp");
	}
}

ya::Backpack::~Backpack()
{
}

void ya::Backpack::Tick()
{
	GameObject::Tick();
}

void ya::Backpack::Render(HDC hdc)
{
	if (mbView)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = pos.x - mImage->GetWidth() * (scale.x / 2.0f);
		finalPos.y = pos.y - mImage->GetHeight() * (scale.y / 2.0f);

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER; ///blend옵션 AC_SRC_OVER: 원본이미지와 다른이미지를 섞는다
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 127; /// 투명도(alpha) 0~255

		AlphaBlend(hdc, finalPos.x, finalPos.y, rect.x, rect.y,
			mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	GameObject::Render(hdc);
}

void ya::Backpack::OnCollisionEnter(Collider* other)
{
}

void ya::Backpack::OnCollisionStay(Collider* other)
{
}

void ya::Backpack::OnCollisionExit(Collider* other)
{
}

void ya::Backpack::Initialize()
{
}
