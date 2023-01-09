#pragma once
#include "yaUIBase.h"

namespace ya
{
	class UITime : public UIBase
	{
	public:
		UITime(eUIType type);
		virtual ~UITime();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	private:
	};
}

