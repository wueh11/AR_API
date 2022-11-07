#pragma once
#include "yaGameObject.h"

namespace ya 
{
	class Image;
	class Backpack : public GameObject
	{
	public:
		Backpack();
		virtual ~Backpack();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void viewToggle() { mbView = !mbView; }

	private:
		float mSpeed;
		Image* mImage;
		bool mbView;
	};
}

