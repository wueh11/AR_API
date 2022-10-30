#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Missile : public GameObject
	{
	public:
		Missile();
		virtual ~Missile();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetSpeed(float speed) { mSpeed = speed; }

	private:
		float mSpeed;
	};
}