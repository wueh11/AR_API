#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class Image;
	class Animator;
	class BombCount : public GameObject
	{
	public:
		BombCount();
		~BombCount();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetPlayer(Player* player) { mPlayer = player; }

	private:
		Image* mImage;
		Animator* mAnimator[2];
		Player* mPlayer;

	};
}

