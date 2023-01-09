#pragma once
#include "yaMonster.h"

// ¹ÖÄá°Ô
namespace ya
{
	class Image;
	class Animator;
	class HugeHermit : public Monster
	{
	public:
		enum class eState
		{
			IDLE,				
			IDLE_CANNON,
			DEPLOY_CANNON,
			FIRING,
			FIRING_CANNON,
			MISSILE,
			CANNON,
			DESTROYED,
		};

		struct MoveState
		{
			bool bAlive = true;
			bool bCannon = false;
			bool bFiring = false;
			bool bMissile = false;
		};

	public:
		HugeHermit();
		virtual ~HugeHermit();

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

	private:
		void Idle();
		void DeployCannon();
		void Firing();
		void Cannon();
		void Missile();
		void Destroyed();

	private:
		void OnIdle();
		void OnAttack();
		void OnAttackComplete();

	private:
		eState mState;
		MoveState mMoveState;
	};
}