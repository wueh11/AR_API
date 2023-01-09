#pragma once
#include "yaGameObject.h"
#include "yaPlayer.h"

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

	public:
		void Idle();
		void Walk();
		void Jump();
		void Fall();
		void JumpMove();
		
	private:
		State mState;
		ya::Player::MoveState mMoveState;
		ya::Player::ControlState mControlState;

		Image* mImage;
		Animator* mAnimator;
	};
}