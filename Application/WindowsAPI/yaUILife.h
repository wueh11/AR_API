#pragma once
#include "yaUIBase.h"

namespace ya
{
	class Image;
	class GameObject;
	class UILife : public UIBase
	{
	public:
		UILife(eUIType type);
		virtual ~UILife();

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

