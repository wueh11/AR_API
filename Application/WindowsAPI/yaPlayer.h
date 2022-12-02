#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Backpack;
	class Rigidbody;
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

			END,
		};

		struct info
		{
			UINT life = 2;
			eArms arms = eArms::Pistol;
			int armsCount = -1;
			UINT bombCount = 10;
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
		void ShootArms();

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

	public:
		void WalkComplete();

	public:
		bool IsLeft() { return mbLeft; }
		bool IsUpside() { return mbUpside; }
		bool IsDownside() { return mbDownside; }
		bool IsJumping() { return mbJump; }
		bool IsSitting() { return mbSit; }
		bool IsFalling() { return mbFall; }

		eArms GetArms() { return mArms; }

	private:
		State mState;

		float mSpeed;
		
		bool mbLeft;
		bool mbUpside;
		bool mbDownside;
		bool mbJump;
		bool mbSit;
		bool mbFall; // 힘을 아래로 받는 상태

		eArms mArms;

		GameObject* mUpper;
		GameObject* mLower;

		Image* mImage;
		Animator* mAnimator;

		//Backpack* mBackpack;
	};
}