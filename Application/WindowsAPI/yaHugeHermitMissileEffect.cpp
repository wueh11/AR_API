#include "yaHugeHermitMissileEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	HugeHermitMissileEffect::HugeHermitMissileEffect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetName(L"HugeHermitMissileEffect");
		SetPos(Vector2::Zero);
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 16.0f, 16.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"HugeHermitMissileEffect", L"..\\Resources\\Image\\Projecttile\\HugeHermitMissileEffect.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"HugeHermitMissileEffect", mImage, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 10, 0.02f);
			mAnimator->GetCompleteEvent(L"HugeHermitMissileEffect") = std::bind(&HugeHermitMissileEffect::Death, this);

			AddComponent(mAnimator);
		}
	}

	HugeHermitMissileEffect::~HugeHermitMissileEffect()
	{
	}

	void HugeHermitMissileEffect::Initialize()
	{
	}

	void HugeHermitMissileEffect::Tick()
	{
		GameObject::Tick();
	}

	void HugeHermitMissileEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HugeHermitMissileEffect::OnCollisionEnter(Collider* other)
	{
	}

	void HugeHermitMissileEffect::OnCollisionStay(Collider* other)
	{
	}
	void HugeHermitMissileEffect::OnCollisionExit(Collider* other)
	{
	}
	void HugeHermitMissileEffect::play()
	{
		mAnimator->Play(L"HugeHermitMissileEffect", false);
	}
}