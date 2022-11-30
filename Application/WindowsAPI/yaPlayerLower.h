#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Player;
	class PlayerLower : public GameObject
	{
	public:
		PlayerLower();
		virtual ~PlayerLower();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void CreateAnimation();

	private:
		Image* mImage;
		Animator* mAnimator;
	};
}