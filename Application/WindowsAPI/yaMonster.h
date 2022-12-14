#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class Monster : public GameObject
	{
	public:
		struct Status
		{
			UINT hp = 100;
			bool alive = true;
		};

	public:
		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	public:
		GameObject* GetTarget() { return mTarget; }
		void SetTarget(GameObject* target) { mTarget = target; }

		Status GetStatus() { return mStatus; }
		void SetHp(int val) { mStatus.hp += val; }

	protected:
		float mSpeed;
		
		Status mStatus;
		GameObject* mTarget;

		Image* mImage;
		Animator* mAnimator;
		Collider* mCollider;
	};
}