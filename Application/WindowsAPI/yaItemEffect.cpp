#include "yaItemEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

namespace ya
{
	ItemEffect::ItemEffect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetName(L"ItemEffect");
		SetPos(Vector2::Zero);
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 16.0f, 16.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"ItemEffect", L"..\\Resources\\Image\\Item\\ItemEffect.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"ItemEffect", mImage, Vector2(0.0f, 0.0f), Vector2(48.0f, 42.0f), Vector2(0.0f, -20.0f), 6, 0.03f);
			mAnimator->GetCompleteEvent(L"ItemEffect") = std::bind(&ItemEffect::Death, this);

			AddComponent(mAnimator);
		}
	}

	ItemEffect::~ItemEffect()
	{
	}

	void ItemEffect::Initialize()
	{
	}

	void ItemEffect::Tick()
	{
		GameObject::Tick();
	}

	void ItemEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ItemEffect::OnCollisionEnter(Collider* other)
	{
	}

	void ItemEffect::OnCollisionStay(Collider* other)
	{
	}
	void ItemEffect::OnCollisionExit(Collider* other)
	{
	}
	void ItemEffect::play()
	{
		mAnimator->Play(L"ItemEffect", false);
	}
}