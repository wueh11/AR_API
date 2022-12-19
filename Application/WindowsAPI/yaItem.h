#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class Item : public GameObject
	{
	public:
		Item();
		virtual ~Item();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	protected:
		Animator* mAnimator;
		Image* mImage;
		Collider* mCollider;
		Rigidbody* mRigidbody;
	};
}