#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class HugeHermitMissile : public GameObject
	{
	private:

	public:
		HugeHermitMissile();
		~HugeHermitMissile();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		float mSpeed;
		float mAliveTime;

		Image* mImage;
		Animator* mAnimator;
		Collider* mCollider;
	};
}