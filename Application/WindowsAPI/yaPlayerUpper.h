#pragma once
#include "yaGameObject.h"
#include "yaPlayer.h"

namespace ya
{
	class Image;
	class Animator;
	class Coliider;
	class Player;
	class PlayerUpper : public GameObject
	{
	public:
		enum class State
		{
			IDLE,				// 0
			WALK,				// 1
			JUMP,				// 2
			WALKJUMP,			// 3
								   
			FRONT_TO_SIT,		// 4
			SIT,				// 5
			SIT_TO_FRONT,		// 6
			SITWALK,			// 7
								   
			FRONT_TO_UPSIDE,	// 8
			UPSIDE,				// 9
			UPSIDE_TO_FRONT,	// 10
								   
			FRONT_TO_DOWNSIDE,	// 11
			DOWNSIDE,			// 12
			DOWNSIDE_TO_FRONT,	// 13
								   
			SHOOT,				// 14
			SHOOT_SIT,			// 15
			SHOOT_UPSIDE,		// 16
			SHOOT_DOWNSIDE,		// 17
								   
			KNIFE,				// 18
			BOMB,				// 19
			
			DIE,
			REVIVAL,

			END,
		};

	public:
		PlayerUpper();
		virtual ~PlayerUpper();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void CreateAnimation();
		
	public:
		void Idle();
		void Walk();
		void Jump();
		void WalkJump();
		
		void FrontToSit();
		void Sit();
		void SitToFront();
		void SitWalk();

		void FrontToUpside();
		void Upside();
		void UpsideToFront();

		void FrontToDownside();
		void Downside();
		void DownsideToFront();

		void Shoot();
		
		void Knife();
		void Bomb();

		void Die();
		void Revival();

	public:
		//void OnIdle();
		void OnWalk();
		void OnSit();
		void OnUpside();
		void OnDownside();

	private:
		State mState;
		ya::Player::MoveState mMoveState;
		ya::Player::ControlState mControlState;
		eArms mArms;

		Image* mImage;
		Animator* mAnimator;
		Collider* mCollider;
	};
}