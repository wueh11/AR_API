#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class CollisionObject : public GameObject
	{
	public:
		CollisionObject();
		~CollisionObject();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	public:
		Image* GetImage() { return mImage; }
		Animator* GetAnimator() { return mAnimator; }

		void SetImage(Image* image) { mImage = image; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

	private:
		Image* mImage;
		Animator* mAnimator;
		Collider* mCollider;
	};
}

