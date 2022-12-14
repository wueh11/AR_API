#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class ChewmeinProjecttile : public GameObject
	{
	private:
		enum class eState
		{
			MOVE,
			DESTROY,
			WAIT,
		};

	public:
		ChewmeinProjecttile();
		~ChewmeinProjecttile();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void Move();
		void Destroy();

	private:
		float mSpeed;
		float mAliveTime;
		eState mState;

		Image* mImage;
		Animator* mAnimator;
		Collider* mCollider;
	};
}