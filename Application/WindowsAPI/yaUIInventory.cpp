#include "yaUIInventory.h"

#include "yaImage.h"
#include "yaPlayer.h"
#include "yaAnimator.h"

namespace ya
{
	UIInventory::UIInventory(eUIType type)
		: UIBase(type)
		, mTarget(nullptr)
		, mArmsCount(nullptr)
		, mBombCount(nullptr)
	{
		SetScale({ M_SCALE, M_SCALE });

		mArmsCount = new ArmsCount;
		mBombCount = new BombCount;
	}

	UIInventory::~UIInventory()
	{
		mArmsCount = nullptr;
		delete mArmsCount;
	}

	void UIInventory::OnInit()
	{
	}

	void UIInventory::OnActive()
	{
	}

	void UIInventory::OnInActive()
	{
	}

	void UIInventory::OnTick()
	{
		mArmsCount->Tick();
		mBombCount->Tick();

		mArmsCount->SetPos(GetPos() + Vector2{ 29.0f, 32.0f });
		mBombCount->SetPos(GetPos() + Vector2{ 108.0f, 32.0f });
	}

	void UIInventory::OnRender(HDC hdc)
	{
		mArmsCount->Render(hdc);
		mBombCount->Render(hdc);

		if (mImage == nullptr)
			return;

		if (mTarget == nullptr)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER; ///blend옵션 AC_SRC_OVER: 원본이미지와 다른이미지를 섞는다
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; /// 투명도(alpha) 0~255

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth() * mScale.x, mImage->GetHeight() * mScale.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void UIInventory::OnClear()
	{
	}
}