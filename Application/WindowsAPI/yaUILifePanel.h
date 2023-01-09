#pragma once
#include "yaUIBase.h"

namespace ya
{
	class UILifePanel : public UIBase
	{
	public:
		UILifePanel(eUIType type);
		~UILifePanel();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	private:
	};
}

