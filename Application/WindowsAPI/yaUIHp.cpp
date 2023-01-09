#include "yaUIHp.h"

#include "yaImage.h"
#include "yaPlayer.h"
#include "yaAnimator.h"

namespace ya
{
	UIHp::UIHp(eUIType type)
		:UIBase(type)
	{
		SetScale({ M_SCALE, M_SCALE });
	}

	UIHp::~UIHp()
	{
	}

	void UIHp::OnInit()
	{
	}

	void UIHp::OnActive()
	{
	}

	void UIHp::OnInActive()
	{
	}

	void UIHp::OnTick()
	{
	}

	void UIHp::OnRender(HDC hdc)
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
			, mImage->GetWidth() * mScale.x, mImage->GetHeight() * mScale.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void UIHp::OnClear()
	{
	}
}