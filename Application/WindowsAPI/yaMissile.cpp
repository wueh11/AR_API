#include "yaMissile.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"

namespace ya
{
	Missile::Missile()
		: mSpeed(800.0f)
		, mAliveTime(5.0f)
		, mDirection(Vector2::One)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 1.0f, 1.0f });
		SetSize({ 24.0f, 24.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"BackPack", L"..\\Resources\\Image\\Bullet\\playerBullet.bmp");
		}

		Collider* collider = new Collider();
		collider->SetSize(GetSize());
		collider->SetScale(GetScale());
		collider->SetOffset({ 0.0f, 0.0f });
		AddComponent(collider);
	}

	Missile::~Missile()
	{
	}

	void Missile::Initialize()
	{
	}

	void Missile::Tick()
	{
		GameObject::Tick();

		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		
		mDirection.Normalize();

		pos.x += mSpeed * mDirection.x * Time::DeltaTime();
		pos.y += mSpeed * mDirection.y * Time::DeltaTime();

		SetPos(pos);

	/*	if (abs(mDirection.x) > 0)
			scale.y = 0.5f;
		else
			scale.y = 1.0f;

		if (abs(mDirection.y) > 0)
			scale.x = 0.5f;
		else
			scale.x = 1.0f;

		SetScale(scale);*/
	}

	void Missile::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 size = GetSize();
		pos = Camera::CalculatePos(pos);
		
		Vector2 rect;
		rect.x = mImage->GetWidth();
		rect.y = mImage->GetHeight();

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, pos.x - (size.x * scale.x / 2), pos.y - (size.y * scale.y / 2), rect.x * scale.x, rect.y * scale.y,
			mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

		GameObject::Render(hdc);
	}

	void Missile::OnCollisionEnter(Collider* other)
	{
		GameObject* gameObj = other->GetOwner();
		gameObj->Death();

		this->Death();
	}

	void Missile::OnCollisionStay(Collider* other)
	{
	}

	void Missile::OnCollisionExit(Collider* other)
	{
	}
}