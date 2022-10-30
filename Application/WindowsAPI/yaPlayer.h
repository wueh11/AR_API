#pragma once
#include "yaGameObject.h"
#include "yaImage.h"

namespace ya
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		float mSpeed;
		Image* mImage;
	};
}