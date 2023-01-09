#include "yaHugeHermitEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	HugeHermitEffect::HugeHermitEffect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetName(L"HugeHermitEffect");
		SetPos(Vector2::Zero);
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 16.0f, 16.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"HugeHermitEffect", L"..\\Resources\\Image\\Projecttile\\HugeHermitEffect.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"HugeHermitEffect", mImage, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 10, 0.02f);
			mAnimator->GetCompleteEvent(L"HugeHermitEffect") = std::bind(&HugeHermitEffect::Death, this);

			AddComponent(mAnimator);
		}
	}

	HugeHermitEffect::~HugeHermitEffect()
	{
	}

	void HugeHermitEffect::Initialize()
	{
	}

	void HugeHermitEffect::Tick()
	{
		GameObject::Tick();
	}

	void HugeHermitEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HugeHermitEffect::OnCollisionEnter(Collider* other)
	{
	}

	void HugeHermitEffect::OnCollisionStay(Collider* other)
	{
	}
	void HugeHermitEffect::OnCollisionExit(Collider* other)
	{
	}
	void HugeHermitEffect::play()
	{
		mAnimator->Play(L"HugeHermitEffect", false);
	}
}