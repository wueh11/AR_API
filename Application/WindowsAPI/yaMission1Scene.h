#pragma once
#include "yaScene.h"
#include "yaMonster.h"

namespace ya
{
	class Mission1Scene : public Scene
	{
	public:
		Mission1Scene();
		~Mission1Scene();

		virtual void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

	};
}