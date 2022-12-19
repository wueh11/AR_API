#include "yaGrenadeEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	GrenadeEffect::GrenadeEffect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetName(L"GrenadeEffect");
		SetPos(Vector2::Zero);
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 16.0f, 16.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"GrenadeEffect", L"..\\Resources\\Image\\Projecttile\\grenadeEffect.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"GrenadeEffect", mImage, Vector2(0.0f, 0.0f), Vector2(50.0f, 106.0f), Vector2(0.0f, -100.0f), 27, 0.02f);
			mAnimator->GetCompleteEvent(L"GrenadeEffect") = std::bind(&GrenadeEffect::Death, this);

			AddComponent(mAnimator);
		}

		AddComponent(new Collider());
	}

	GrenadeEffect::~GrenadeEffect()
	{
	}

	void GrenadeEffect::Initialize()
	{
	}

	void GrenadeEffect::Tick()
	{
		GameObject::Tick();
	}

	void GrenadeEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void GrenadeEffect::OnCollisionEnter(Collider* other)
	{
	}

	void GrenadeEffect::OnCollisionStay(Collider* other)
	{
	}
	void GrenadeEffect::OnCollisionExit(Collider* other)
	{
	}
	void GrenadeEffect::play()
	{
		mAnimator->Play(L"GrenadeEffect", false);
	}
}