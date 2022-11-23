#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Hostage : public GameObject
	{
	public:
		Hostage();
		~Hostage();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		float mSpeed;
		Image* mImage;
	};
}

