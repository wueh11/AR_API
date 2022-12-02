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
		enum class State
		{
			IDLE,
			WALK,
			JUMP,
			FALL,
			JUMPMOVE,
			END,
		};

		PlayerLower();
		virtual ~PlayerLower();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		void Idle(bool bLeft);
		void Walk(bool bLeft);
		void Jump(bool bLeft, bool bJump, bool bFall);
		void Fall(bool bLeft, bool bJump);
		void JumpMove(bool bLeft, bool bJump);
		
	private:
		State mState;

		Image* mImage;
		Animator* mAnimator;
	};
}