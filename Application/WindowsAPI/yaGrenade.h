#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Grenade : public GameObject
	{
	public:
		Grenade();
		virtual ~Grenade();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetSpeed(float speed) { mSpeed = speed; }
		void SetDirection(Vector2 direction) { mDirection = direction; }

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		float mSpeed;
		float mAliveTime;
		Vector2 mDirection;

		Image* mImage;
		Animator* mAnimator;

		UINT mBounceCount;
	};
}