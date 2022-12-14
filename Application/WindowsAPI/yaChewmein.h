#pragma once
#include "yaMonster.h"

// 밍콩게
namespace ya
{
	class Image;
	class Animator;
	class Chewmein : public Monster
	{
	public:
		enum class eState
		{
			IDLE,				// 0
			WALK_FRONT,			// 1
			WALK_BACK,			// 2
			TURN,				// 3
			JUMP,				// 4
			ATTACK,				// 5
			ATTACK_BUBBLE,		// 6
			DIE,
			END,
		};

		struct MoveState
		{
			bool bLeft = true;
			bool bWalk = false;
			bool bJump = false;
			bool bFall = true; // 힘을 아래로 받는 상태

			void clear()
			{
				bWalk = false;
				bJump = false;
				bFall = true;
			}
		};

	public:
		Chewmein();
		~Chewmein();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	public:
		void SetState(eState state) { mState = state; }
		eState GetState() { return mState; }

		MoveState GetMoveState() { return mMoveState; }

		void SetLeft(bool left) { mMoveState.bLeft = left; }

	private:
		void Idle();
		void WalkFront();
		void WalkBack();
		void Turn();
		void Jump();
		void Attack();
		void AttackBubble();
		void Die();

	private:
		void OnIdle();

	private:
		eState mState;
		MoveState mMoveState;
	};
}