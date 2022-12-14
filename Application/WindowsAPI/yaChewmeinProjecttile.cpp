#include "yaChewmeinProjecttile.h"

#include "yaResources.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaImage.h"
#include "yaAnimator.h"

namespace ya
{
	ChewmeinProjecttile::ChewmeinProjecttile()
		: mSpeed(800.0f)
		, mAliveTime(5.0f)
		, mImage(nullptr)
		, mState(eState::MOVE)
	{
		SetPos({ 100.0f, 100.0f });
		//SetScale({ M_SCALE, M_SCALE });
		SetSize({ 12.0f, 12.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"chewmein_projecttile", L"..\\Resources\\Image\\Monster\\chewmein_projecttile.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"projecttile", mImage, Vector2(0.0f, 0.0f), Vector2(19.0f, 16.0f), Vector2(0.0f, 0.0f), 8, 0.08f);
			mAnimator->CreateAnimation(L"projecttile_destory", mImage, Vector2(0.0f, 18.0f), Vector2(40.0f, 32.0f), Vector2(0.0f, 0.0f), 13, 0.02f);
			mAnimator->GetCompleteEvent(L"projecttile_destory") = std::bind(&ChewmeinProjecttile::Death, this);
			AddComponent(mAnimator);
			mAnimator->Play(L"projecttile", true);
		}
		 
		mCollider = new Collider();
		mCollider->SetSize(GetSize());
		mCollider->SetScale(GetScale());
		mCollider->SetOffset({ 0.0f, 0.0f });
		AddComponent(mCollider);
	}
	ChewmeinProjecttile::~ChewmeinProjecttile()
	{
	}
	void ChewmeinProjecttile::Initialize()
	{
	}
	void ChewmeinProjecttile::Tick()
	{
		GameObject::Tick();

		switch (mState)
		{
		case ya::ChewmeinProjecttile::eState::MOVE:
			Move();
			break;
		case ya::ChewmeinProjecttile::eState::DESTROY:
			Destroy();
			break;
		case ya::ChewmeinProjecttile::eState::WAIT:
			break;
		default:
			break;
		}
	}
	void ChewmeinProjecttile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ChewmeinProjecttile::OnCollisionEnter(Collider* other)
	{
		mState = eState::DESTROY;
	}
	void ChewmeinProjecttile::OnCollisionStay(Collider* other)
	{
	}
	void ChewmeinProjecttile::OnCollisionExit(Collider* other)
	{
	}
	void ChewmeinProjecttile::Move()
	{
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			mState = eState::DESTROY;
		}

		Vector2 scale = GetScale();
		scale += 2.0f * Time::DeltaTime();
		if (scale.x > M_SCALE)
		{
			scale.x = M_SCALE;
			scale.y = M_SCALE;
		}
		SetScale(scale);

		Vector2 pos = GetPos();
		pos.x -= 120.0f * Time::DeltaTime();
		pos.y -= sinf(math::DegreeToRadian(mAliveTime * 100.0f)) * 20.0f * Time::DeltaTime();

		SetPos(pos);
	}
	void ChewmeinProjecttile::Destroy()
	{
		mCollider->SetActive(false);
		mAnimator->Play(L"projecttile_destory", false);

		mState = eState::WAIT;
	}
}