#include "yaChewmein.h"

#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaImage.h"
#include "yaResources.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"

namespace ya
{
	Chewmein::Chewmein()
		: mSpeed(1.0f)
	{
		SetName(L"Chewmein");
		SetPos({ 450.0f, 100.0f });
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 100.0f, 100.0f });
		Initialize();
	}

	Chewmein::~Chewmein()
	{
	}

	void Chewmein::Initialize()
	{
		GetObjectInfo().SetHp(100);

		{ // 애니메이션
			if (mImage == nullptr)
				//mImage = Resources::Load<Image>(L"Chewmein", L"..\\Resources\\Image\\metalslug3\\mission_1\\Monster\\chewmein_idle.bmp");
				mImage = Resources::Load<Image>(L"Chewmein", L"..\\Resources\\Image\\chewmein_idle.bmp");

			//SetSize(Vector2(66.2f, 45.0f)*GetScale());
			 
			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"cIdle", mImage
				, Vector2(0.0f, 0.0f), Vector2(66.2f, 45.0f)
				, Vector2(0.0f, 0.0f), 7, 0.1f);

			mAnimator->Play(L"cIdle", true);

			AddComponent(mAnimator);
		}

		AddComponent(new Collider());
	}

	void Chewmein::Tick()
	{
		GameObject::Tick();
	}

	void Chewmein::Render(HDC hdc)
	{
		/*Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = pos.x - mImage->GetWidth() * (scale.x / 2.0f);
		finalPos.y = pos.y - mImage->GetHeight() * (scale.y / 2.0f);

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		finalPos = Camera::CalculatePos(finalPos);

		TransparentBlt(hdc, finalPos.x, finalPos.y
			, rect.x, rect.y, mImage->GetDC()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));*/

		GameObject::Render(hdc);
	}

	void Chewmein::OnCollisionEnter(Collider* other)
	{
	}

	void Chewmein::OnCollisionStay(Collider* other)
	{
	}

	void Chewmein::OnCollisionExit(Collider* other)
	{
	}
}