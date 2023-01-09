#pragma once
#include "yaUIBase.h"

namespace ya
{
	class Image;
	class GameObject;
	class UIHp : public UIBase
	{
	public:
		UIHp(eUIType type);
		virtual ~UIHp();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void SetTarget(GameObject* target) { mTarget = target; }

	private:
		GameObject* mTarget;
	};
}

