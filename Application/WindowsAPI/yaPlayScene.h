#pragma once
#include "yaScene.h"
#include "yaMonster.h"

namespace ya
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();
	private:
		Monster* mons[2];
	};
}