#include "yaHugeHermit.h"

#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaTime.h"
#include "yaCamera.h"
#include "yaInput.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

namespace ya
{
	HugeHermit::HugeHermit()
		: Monster()
		, mState(eState::IDLE)
	{
		SetName(L"HugeHermit");
		SetPos({ 600.0f, 200.0f });
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 32.0f, 40.0f });

		mSpeed = 300.0f;
		mStatus.SetHp(40);

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"HugeHermit", L"..\\Resources\\Image\\Monster\\HugeHermit\\HugeHermit.bmp");

			mAnimator = AddComponent<Animator>();

			mAnimator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 32.0f), Vector2(230.0f, 207.0f), Vector2(0.0f, 0.0f), 12, 0.1f);
			mAnimator->CreateAnimation(L"DeployCannon", mImage, Vector2(0.0f, 291.0f), Vector2(230.0f, 208.0f), Vector2(0.0f, 0.0f), 12, 0.1f);
			mAnimator->CreateAnimation(L"IdleCannon", mImage, Vector2(0.0f, 554.0f), Vector2(230.0f, 206.0f), Vector2(0.0f, 0.0f), 12, 0.1f);
			mAnimator->CreateAnimation(L"FiringCannon", mImage, Vector2(0.0f, 804.0f), Vector2(228.0f, 206.0f), Vector2(0.0f, 0.0f), 12, 0.1f);
			mAnimator->CreateAnimation(L"Firing", mImage, Vector2(0.0f, 1018.0f), Vector2(229.0f, 206.0f), Vector2(0.0f, 0.0f), 12, 0.1f);
			mAnimator->CreateAnimation(L"Destoryed", mImage, Vector2(0.0f, 1277.0f), Vector2(230.0f, 181.0f), Vector2(0.0f, 0.0f), 12, 0.1f);

			mAnimator->GetCompleteEvent(L"DeployCannon") = std::bind(&HugeHermit::Death, this);
			//mAnimator->GetCompleteEvent(L"DieRight") = std::bind(&HugeHermit::Death, this);

			mAnimator->Play(L"Idle", true);
		}

		Scene* playScene = SceneManager::GetPlayScene();
	}

	HugeHermit::~HugeHermit()
	{
		/*for (GameObject* object : mChildren)
		{
			if (object == nullptr)
				continue;

			delete object;
			object = nullptr;
		}*/
	}

	void HugeHermit::Initialize()
	{
		Monster::Initialize();
	}

	void HugeHermit::Tick()
	{
		Monster::Tick();
	}

	void HugeHermit::Render(HDC hdc)
	{
		Vector2 pos = Camera::CalculatePos(GetPos());

		wchar_t szFloat[50] = {};
		std::wstring str = L"[" + std::to_wstring((int)mState) + L"] HP:" + std::to_wstring((int)mStatus.hp);
		swprintf_s(szFloat, 50, str.c_str());
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, pos.x - 20.0f, pos.y - 80.0f, szFloat, strLen);

		Monster::Render(hdc);
	}

	void HugeHermit::OnCollisionEnter(Collider* other)
	{
		Monster::OnCollisionEnter(other);
	}

	void HugeHermit::OnCollisionStay(Collider* other)
	{
	}

	void HugeHermit::OnCollisionExit(Collider* other)
	{
	}

	void HugeHermit::Idle()
	{
	}

	void HugeHermit::DeployCannon()
	{
	}

	void HugeHermit::Firing()
	{
	}

	void HugeHermit::Cannon()
	{
	}

	void HugeHermit::Missile()
	{
	}

	void HugeHermit::Destroyed()
	{
	}
}