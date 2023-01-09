#include "yaUITime.h"
#include "yaImage.h"

namespace ya
{
	UITime::UITime(eUIType type)
		: UIBase(type)
	{
	}

	UITime::~UITime()
	{
	}

	void UITime::OnInit()
	{
	}

	void UITime::OnActive()
	{
	}

	void UITime::OnInActive()
	{
	}

	void UITime::OnTick()
	{
	}

	void UITime::OnRender(HDC hdc)
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

	void UITime::OnClear()
	{
	}


}