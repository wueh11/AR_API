#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Backpack;
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void WalkComplete();

		bool IsLeft() { return mLeft; }

	private:
		float mSpeed;
		
		bool mLeft;
		bool mJump;

		GameObject* mUpper;
		GameObject* mLower;

		Image* mImage;
		Animator* mAnimator;

		Backpack* mBackpack;
	};
}