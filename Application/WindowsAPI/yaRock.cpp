#include "yaRock.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"

namespace ya
{
	Rock::Rock()
		: mSpeed((rand() % 600) + 100)
		, mAliveTime(5.0f)
	{
		SetPos({ (float)((rand() % 1920)), 0.0f });
		SetScale({ 1.0f, 1.0f });
		SetSize	({ (float)((rand() % 50) + 50), (float)((rand() % 50) + 50) });

		Collider* col = new Collider();
		AddComponent(col);
	}

	Rock::~Rock()
	{
	}

	void Rock::Initialize()
	{
	}

	void Rock::Tick()
	{
		GameObject::Tick();

		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}

		Vector2 pos = GetPos();
		pos.y += mSpeed * Time::DeltaTime();
		SetPos(pos);
	}

	void Rock::Render(HDC hdc)
	{
		HBRUSH blueBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		Brush brush(hdc, blueBrush);

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 size = GetSize();
		pos = Camera::CalculatePos(pos);

		Ellipse(hdc, pos.x, pos.y, pos.x + size.x, pos.y + size.y);

		GameObject::Render(hdc);
	}

	void Rock::OnCollisionEnter(Collider* other)
	{
		//this->Death();
	}

	void Rock::OnCollisionStay(Collider* other)
	{
	}

	void Rock::OnCollisionExit(Collider* other)
	{
	}
}