#pragma once
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	class Image;
	class Animator;
	class Rigidbody;
	class PlayerUpper;
	class PlayerLower;
	class Player : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			WALK,
			JUMP,
			SIT,

			FRONT_TO_UPSIDE,
			UPSIDE,
			UPSIDE_TO_FRONT,
			FRONT_TO_DOWNSIDE,
			DOWNSIDE,
			DOWNSIDE_TO_FRONT,

			SHOOT,
			/*SHOOT_FRONT_UPSIDE,
			SHOOT_UPSIDE,
			SHOOT_DOWNSIDE,
			SHOOT_SIT,*/

			KNIFE,
			/*KNIFE_JUMP,
			KNIFE_SIT,*/

			BOMB,
			//BOMB_SIT,

			DIE,
			REVIVAL,

			RESET,
			END,
		};

		struct Info
		{
			UINT life = 2;
			eArms arms = eArms::Pistol;
			int armsCount = -1;
			UINT bombCount = 10;
		};

		struct ControlState
		{
			bool bAlive = true;			// 살았는지
			bool bInvincible = false;	// 무적
			bool bPlayable = true;		// 조작 가능한지
			bool bRevival = false;		// 부활중
		};

		struct MoveState
		{
			bool bLeft = false;
			bool bWalk = false;
			bool bUpside = false;
			bool bDownside = false;
			bool bJump = false;
			bool bSit = false;
			bool bFall = true; // 힘을 아래로 받는 상태
			bool bKnife = false;
			
			//void SetKnife(bool knife) { bKnife = knife; }

			void Clear()
			{
				bWalk = false;
				bUpside = false;
				bDownside = false;
				bJump = false;
				bSit = false;
				bFall = true;
				bKnife = false;
			}
		};

		Player();
		virtual ~Player();

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
		void Sit();
		void Upside();
		void Downside();

		void Shoot();
		void Knife();
		void Bomb();

		void Die();
		void Revival();

		void Reset();

	private:
		void OnShoot();
		void OnKnife();
		void OnBomb();

	public:
		void PickupArms(eArms arms, UINT bulletCount);

	public:
		void Attacked();

		Info GetInfo() { return mInfo; }
		eArms GetArms() { return mInfo.arms; }
		void SetArms(eArms arms) { mInfo.arms = arms; }
		void SetArmsCount(int count) { mInfo.armsCount = count; }
		void SetBombCount(int count) { mInfo.bombCount = count; }

		MoveState GetMoveState() { return mMoveState; }
		ControlState GetControlState() { return mControlState; }
		
		void SetState(State state) { mState = state; }
		void SetKnife(bool knife) { mMoveState.bKnife = knife; }

	private:
		State mState;
		State mBeforeState;

		MoveState mMoveState;
		ControlState mControlState;
		Info mInfo;

		float mSpeed;
		Vector2 mArmsDirection;
		
		PlayerUpper* mUpper;
		PlayerLower* mLower;

		Image* mImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
	};
}