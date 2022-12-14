#include "yaWaterFront.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	WaterFront::WaterFront()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"WaterFront", L"..\\Resources\\Image\\Background\\part1\\2.7\\water_front_sprite.bmp");

			mAnimator = new Animator();

			mAnimator->CreateAnimation(L"WaterFront", mImage, Vector2(0.0f, 0.0f), Vector2(1420.0f, 110.0f), Vector2(0.0f, 0.0f), 5, 0.2f, true, true);
			mAnimator->Play(L"WaterFront", true);

			AddComponent(mAnimator);
		}
	}

	WaterFront::~WaterFront()
	{
	}

	void WaterFront::Initialize()
	{
	}

	void WaterFront::Tick()
	{
		GameObject::Tick();
	}

	void WaterFront::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}