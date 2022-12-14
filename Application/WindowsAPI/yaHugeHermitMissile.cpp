#include "yaHugeHermitMissile.h"

#include "yaResources.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaImage.h"
#include "yaAnimator.h"

namespace ya
{
	HugeHermitMissile::HugeHermitMissile()
		: mSpeed(800.0f)
		, mAliveTime(5.0f)
		, mImage(nullptr)
		, mCollider(nullptr)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 12.0f, 12.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"chewmein_projecttile", L"..\\Resources\\Image\\Monster\\chewmein_projecttile.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"projecttile", mImage, Vector2(0.0f, 0.0f), Vector2(19.0f, 16.0f), Vector2(0.0f, 0.0f), 8, 0.08f);
			mAnimator->CreateAnimation(L"projecttile_destory", mImage, Vector2(0.0f, 18.0f), Vector2(40.0f, 32.0f), Vector2(0.0f, 0.0f), 13, 0.02f);
			mAnimator->GetCompleteEvent(L"projecttile_destory") = std::bind(&HugeHermitMissile::Death, this);
			AddComponent(mAnimator);
			mAnimator->Play(L"projecttile", true);
		}

		Collider* collider = AddComponent<Collider>();
	}

	HugeHermitMissile::~HugeHermitMissile()
	{
	}

	void HugeHermitMissile::Initialize()
	{
	}
	void HugeHermitMissile::Tick()
	{
		GameObject::Tick();
	}
	void HugeHermitMissile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HugeHermitMissile::OnCollisionEnter(Collider* other)
	{
	}
	void HugeHermitMissile::OnCollisionStay(Collider* other)
	{
	}
	void HugeHermitMissile::OnCollisionExit(Collider* other)
	{
	}
}