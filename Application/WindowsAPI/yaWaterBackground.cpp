#include "yaWaterBackground.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	WaterBackground::WaterBackground()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"WaterBackground", L"..\\Resources\\Image\\Background\\part1\\2.7\\water_background_sprite.bmp");

			mAnimator = new Animator();

			mAnimator->CreateAnimation(L"WaterBackground", mImage, Vector2(0.0f, 0.0f), Vector2(1420.0f, 70.0f), Vector2(0.0f, 0.0f), 8, 0.2f, true, true);
			mAnimator->Play(L"WaterBackground", true);

			AddComponent(mAnimator);
		}
	}

	WaterBackground::~WaterBackground()
	{
	}

	void WaterBackground::Initialize()
	{
	}

	void WaterBackground::Tick()
	{
		GameObject::Tick();
	}

	void WaterBackground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}