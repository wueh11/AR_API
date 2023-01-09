#include "yaUILife.h"

#include "yaImage.h"
#include "yaPlayer.h"
#include "yaAnimator.h"

namespace ya
{
	UILife::UILife(eUIType type)
		:UIBase(type)
	{
	}

	UILife::~UILife()
	{
	}

	void UILife::OnInit()
	{
	}

	void UILife::OnActive()
	{
	}

	void UILife::OnInActive()
	{
	}

	void UILife::OnTick()
	{
	}

	void UILife::OnRender(HDC hdc)
	{
		if (mImage == nullptr)
			return;

		if (mTarget == nullptr)
			return;

		Player* playerObj = dynamic_cast<Player*>(mTarget);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER; ///blend�ɼ� AC_SRC_OVER: �����̹����� �ٸ��̹����� ���´�
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; /// ����(alpha) 0~255

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void UILife::OnClear()
	{
	}
}