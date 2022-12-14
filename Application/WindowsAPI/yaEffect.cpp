#include "yaEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	Effect::Effect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetName(L"Effect");
		SetPos(Vector2::Zero);
		SetScale({ M_SCALE, M_SCALE });
		SetSize({16.0f, 16.0f});

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"bulletEffect", L"..\\Resources\\Image\\Bullet\\bulletEffect.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"bulletEffect", mImage, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 10, 0.02f);
			mAnimator->GetCompleteEvent(L"bulletEffect") = std::bind(&Effect::Death, this);

			AddComponent(mAnimator);
		}
	}

	Effect::~Effect()
	{
	}

	void Effect::Initialize()
	{
	}

	void Effect::Tick()
	{
		GameObject::Tick();

		/*mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}

		Vector2 pos = GetPos();
		SetPos(pos);*/
	}

	void Effect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Effect::OnCollisionEnter(Collider* other)
	{
	}

	void Effect::OnCollisionStay(Collider* other)
	{
	}
	void Effect::OnCollisionExit(Collider* other)
	{
	}
	void Effect::play()
	{
		mAnimator->Play(L"bulletEffect", false);
	}
}