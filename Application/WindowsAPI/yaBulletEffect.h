#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class BulletEffect : public GameObject
	{
	public:
		BulletEffect();
		~BulletEffect();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void play();

	private:
		float mSpeed;
		float mAliveTime;

		Image* mImage;
		Animator* mAnimator;
	};
}
