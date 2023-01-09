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
		func.BlendOp = AC_SRC_OVER; ///blend�ɼ� AC_SRC_OVER: �����̹����� �ٸ��̹����� ���´�
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; /// ����(alpha) 0~255

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void UILifePanel::OnClear()
	{
	}


}