#include "yaRock.h"
#include "yaTime.h"

namespace ya
{
	Rock::Rock()
		: mSpeed((rand() % 600) + 100)
	{
		SetPos({ (float)((rand() % 1920)), 0.0f });
		SetScale({ (float)((rand() % 50) + 50), (float)((rand() % 50) + 50) });
	}

	Rock::~Rock()
	{
	}

	void Rock::Initialize()
	{
	}

	void Rock::Tick()
	{
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

		Ellipse(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);

		GameObject::Render(hdc);
	}
}