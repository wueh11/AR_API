#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class HugeHermitCannonCollisionEffect : public GameObject
	{
	public:
		HugeHermitCannonCollisionEffect();
		~HugeHermitCannonCollisionEffect();

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
