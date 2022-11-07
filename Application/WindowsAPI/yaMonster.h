#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(Vector2 position);
		~Monster();

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