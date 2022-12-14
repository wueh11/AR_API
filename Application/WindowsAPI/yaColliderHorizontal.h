#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Collider;
	class ColliderHorizontal : public GameObject
	{
	public:
		ColliderHorizontal();
		virtual ~ColliderHorizontal();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Collider* mCollider;
	};
}

