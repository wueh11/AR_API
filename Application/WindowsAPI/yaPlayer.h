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
			SHOOT_FRONT_UPSIDE,
			SHOOT_UPSIDE,
			SHOOT_DOWNSIDE,

			KNIFE,
			BOMB,

			DIE,

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
			bool bAlive = true;
			bool bInvincible = false;	// 무적
			bool bPlayable = true;		// 조작 가능한지
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
			
			void clear()
			{
				bWalk = false;
				bUpside = false;
				bDownside = false;
				bJump = false;
				bSit = false;
				bFall = true;
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
		void Jump(Rigidbody* rigidbody);
		void Sit();
		void Upside();
		void Downside();
		void Shoot();
		void ShootFrontUpside();
		void ShootUpside();
		void ShootDownside();
		void Knife();
		void Bomb();
		void Die();

	private:
		void OnShoot();
		void OnWalk();

	public:
		void PickupArms(eArms arms, UINT bulletCount);
		void WalkComplete();

	public:
		eArms GetArms() { return mInfo.arms; }
		MoveState GetMoveState() { return mMoveState; }
		ControlState GetControlState() { return mControlState; }

	private:
		State mState;
		MoveState mMoveState;
		ControlState mControlState;
		Info mInfo;

		float mSpeed;
		Vector2 mArmsDirection;
		
		PlayerUpper* mUpper;
		PlayerLower* mLower;

		Image* mImage;
		Animator* mAnimator;
	};
}