#include "yaEffect.h"

#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"

#include "yaImage.h"
#include "yaAnimator.h"


namespace ya
{
	Effect::Effect()
		: mSpeed(1.0f)
		, mAliveTime(1.0f)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 20.0f, 20.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Find<Image>(L"Player");
		}
		Animator* ani = new Animator();
		ani->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 3, 0.1f);

		ani->Play(L"Idle", true);

		AddComponent(ani);
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

		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}

		Vector2 pos = GetPos();
		SetPos(pos);
	}

	void Effect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}