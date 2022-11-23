#pragma once
#include "yaScene.h"

namespace ya
{
	class CharacterSelectScene : public Scene
	{
	public:
		CharacterSelectScene();
		~CharacterSelectScene();

		virtual void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

	};
}