#include "yaHugeHermitCannonFireEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	HugeHermitCannonFireEffect::HugeHermitCannonFireEffect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetName(L"HugeHermitCannonFireEffect");
		SetPos(Vector2::Zero);
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 16.0f, 16.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"HugeHermitCannonFireEffect", L"..\\Resources\\Image\\Projecttile\\HugeHermitCannonFireEffect.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"HugeHermitCannonFireEffect", mImage, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 10, 0.02f);
			mAnimator->GetCompleteEvent(L"HugeHermitCannonFireEffect") = std::bind(&HugeHermitCannonFireEffect::Death, this);

			AddComponent(mAnimator);
		}
	}

	HugeHermitCannonFireEffect::~HugeHermitCannonFireEffect()
	{
	}

	void HugeHermitCannonFireEffect::Initialize()
	{
	}

	void HugeHermitCannonFireEffect::Tick()
	{
		GameObject::Tick();
	}

	void HugeHermitCannonFireEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HugeHermitCannonFireEffect::OnCollisionEnter(Collider* other)
	{
	}

	void HugeHermitCannonFireEffect::OnCollisionStay(Collider* other)
	{
	}
	void HugeHermitCannonFireEffect::OnCollisionExit(Collider* other)
	{
	}
	void HugeHermitCannonFireEffect::play()
	{
		mAnimator->Play(L"HugeHermitCannonFireEffect", false);
	}
}