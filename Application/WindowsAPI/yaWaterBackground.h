#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class WaterBackground : public GameObject
	{
	public:
		WaterBackground();
		~WaterBackground();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Image* mImage;
		Animator* mAnimator;
	};
}

