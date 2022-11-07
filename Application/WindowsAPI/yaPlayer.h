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
		void Walking();

	private:
		float mSpeed;
		Image* mImage;
		Animator* mAnimator;

		Backpack* mBackpack;
	};
}