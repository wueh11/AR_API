#include "yaBulletEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	BulletEffect::BulletEffect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetName(L"BulletEffect");
		SetPos(Vector2::Zero);
		SetScale({ M_SCALE, M_SCALE });
		SetSize({16.0f, 16.0f});

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"bulletEffect", L"..\\Resources\\Image\\Projecttile\\bullet_effect.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"bulletEffect", mImage, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 10, 0.02f);
			mAnimator->GetCompleteEvent(L"bulletEffect") = std::bind(&BulletEffect::Death, this);

			AddComponent(mAnimator);
		}
	}

	BulletEffect::~BulletEffect()
	{
	}

	void BulletEffect::Initialize()
	{
	}

	void BulletEffect::Tick()
	{
		GameObject::Tick();
	}

	void BulletEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BulletEffect::OnCollisionEnter(Collider* other)
	{
	}

	void BulletEffect::OnCollisionStay(Collider* other)
	{
	}
	void BulletEffect::OnCollisionExit(Collider* other)
	{
	}
	void BulletEffect::play()
	{
		mAnimator->Play(L"bulletEffect", false);
	}
}