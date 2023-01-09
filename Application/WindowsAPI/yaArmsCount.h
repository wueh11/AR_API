#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class Image;
	class Animator;
	class ArmsCount : public GameObject
	{
	public:
		ArmsCount();
		~ArmsCount();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetPlayer(Player* player) { mPlayer = player; }

	private:
		Image* mImage;
		Animator* mAnimator[3];
		Player* mPlayer;
		
	};
}

