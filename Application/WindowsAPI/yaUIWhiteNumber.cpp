#include "yaUINumber.h"

#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	UINumber::UINumber(eUIType type)
		: UIBase(type)
	{
		SetSize({ 8.0f, 8.0f });
		//mImage = Resources::Load<Image>(L"number_yellow_0", L"..\\Resources\\Image\\UI\\player_upper_pistol.bmp");
		mValue = L"0";
	}

	UINumber::~UINumber()
	{
	}

	void UINumber::OnInit()
	{
	}

	void UINumber::OnActive()
	{
	}

	void UINumber::OnInActive()
	{
	}

	void UINumber::OnTick()
	{
		mImage = Resources::Load<Image>(L"number_yellow_0", L"..\\Resources\\Image\\UI\\text_white_" + mValue + L".bmp");
	}

	void UINumber::OnRender(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER; ///blend옵션 AC_SRC_OVER: 원본이미지와 다른이미지를 섞는다
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; /// 투명도(alpha) 0~255

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void UINumber::OnClear()
	{
	}


}