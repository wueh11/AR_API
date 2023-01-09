#include "yaHugeHermitCannonCollisionEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	HugeHermitCannonCollisionEffect::HugeHermitCannonCollisionEffect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetName(L"HugeHermitCannonCollisionEffect");
		SetPos(Vector2::Zero);
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 16.0f, 16.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"HugeHermitCannonCollisionEffect", L"..\\Resources\\Image\\Projecttile\\HugeHermitCannonCollisionEffect.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"HugeHermitCannonCollisionEffect", mImage, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 10, 0.02f);
			mAnimator->GetCompleteEvent(L"HugeHermitCannonCollisionEffect") = std::bind(&HugeHermitCannonCollisionEffect::Death, this);

			AddComponent(mAnimator);
		}
	}

	HugeHermitCannonCollisionEffect::~HugeHermitCannonCollisionEffect()
	{
	}

	void HugeHermitCannonCollisionEffect::Initialize()
	{
	}

	void HugeHermitCannonCollisionEffect::Tick()
	{
		GameObject::Tick();
	}

	void HugeHermitCannonCollisionEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HugeHermitCannonCollisionEffect::OnCollisionEnter(Collider* other)
	{
	}

	void HugeHermitCannonCollisionEffect::OnCollisionStay(Collider* other)
	{
	}
	void HugeHermitCannonCollisionEffect::OnCollisionExit(Collider* other)
	{
	}
	void HugeHermitCannonCollisionEffect::play()
	{
		mAnimator->Play(L"HugeHermitCannonCollisionEffect", false);
	}
}