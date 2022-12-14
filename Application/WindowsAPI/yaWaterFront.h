#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class WaterFront : public GameObject
	{
	public:
		WaterFront();
		~WaterFront();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Image* mImage;
		Animator* mAnimator;
	};
}

