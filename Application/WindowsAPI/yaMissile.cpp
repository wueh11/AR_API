#include "yaMissile.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"

namespace ya
{
	Missile::Missile()
		: mSpeed(300.0f)
		, mAliveTime(5.0f)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 1.0f, 1.0f });
		SetSize({ 10.0f, 10.0f });

		Collider* col = new Collider();

		AddComponent(col);
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
		pos.x += mSpeed * Time::DeltaTime();
		SetPos(pos);
	}

	void Missile::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 size = GetSize();
		pos = Camera::CalculatePos(pos);

		Ellipse(hdc, pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y);

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