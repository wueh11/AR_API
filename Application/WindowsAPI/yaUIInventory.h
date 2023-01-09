#pragma once
#include "yaUIBase.h"
#include "yaArmsCount.h"
#include "yaBombCount.h"

namespace ya
{
	class Image;
	class GameObject;
	class UIInventory : public UIBase
	{
		enum class character
		{
			NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
		};

	public:
		UIInventory(eUIType type);
		virtual ~UIInventory();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void SetTarget(GameObject* target) { mTarget = target; }

	private:
		GameObject* mTarget;
		ArmsCount* mArmsCount;
		BombCount* mBombCount;
	};
}

