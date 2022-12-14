#include "yaWaterEffect.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	WaterEffect::WaterEffect()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eState::DEFAULT)
	{
		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"WaterEffect", L"..\\Resources\\Image\\Background\\part1\\2.7\\water_effect.bmp");

			mAnimator = new Animator();

			mAnimator->CreateAnimation(L"Walk", mImage, Vector2(0.0f, 0.0f), Vector2(180.0f, 46.0f), Vector2(0.0f, -5.0f), 4, 0.1f);
			mAnimator->CreateAnimation(L"Jump", mImage, Vector2(0.0f, 72.0f), Vector2(180.0f, 80.0f), Vector2(0.0f, 0.0f), 5, 0.1f);
			mAnimator->CreateAnimation(L"Fall", mImage, Vector2(0.0f, 170.0f), Vector2(180.0f, 80.0f), Vector2(0.0f, -25.0f), 6, 0.1f);

			mAnimator->GetCompleteEvent(L"Fall") = std::bind(&WaterEffect::Walk, this);
			mAnimator->GetCompleteEvent(L"Jump") = std::bind(&WaterEffect::Hide, this);

			mAnimator->Play(L"Default", true);

			AddComponent(mAnimator);
		}
	}

	WaterEffect::~WaterEffect()
	{
	}

	void WaterEffect::Initialize()
	{
	}

	void WaterEffect::Tick()
	{
		GameObject::Tick();

		switch (mState)
		{
		case ya::WaterEffect::eState::DEFAULT:
			Defalut();
			break;
		case ya::WaterEffect::eState::WALK:
			Walk();
			break;
		case ya::WaterEffect::eState::JUMP:
			Jump();
			break;
		case ya::WaterEffect::eState::FALL:
			Fall();
			break;
		default:
			break;
		}
	}

	void WaterEffect::Render(HDC hdc)
	{
		if (!mbShow)
			return;

		GameObject::Render(hdc);
	}

	void WaterEffect::Defalut()
	{
	}

	void WaterEffect::Walk()
	{
		mAnimator->Play(L"Walk", true);
		mState = eState::DEFAULT;
	}

	void WaterEffect::Jump()
	{
		mAnimator->Play(L"Jump", false);
		mState = eState::DEFAULT;
	}

	void WaterEffect::Fall()
	{
		mAnimator->Play(L"Fall", false);
		mbShow = true;
		mState = eState::DEFAULT;
	}
}