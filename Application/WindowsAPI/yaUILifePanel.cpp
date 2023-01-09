#include "yaUILifePanel.h"
#include "yaImage.h"

namespace ya
{
	UILifePanel::UILifePanel(eUIType type)
		: UIBase(type)
	{
	}

	UILifePanel::~UILifePanel()
	{
	}

	void UILifePanel::OnInit()
	{
	}

	void UILifePanel::OnActive()
	{
	}

	void UILifePanel::OnInActive()
	{
	}

	void UILifePanel::OnTick()
	{
	}

	void UILifePanel::OnRender(HDC hdc)
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

	void UILifePanel::OnClear()
	{
	}


}