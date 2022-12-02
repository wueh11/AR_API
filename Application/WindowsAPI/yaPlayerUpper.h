#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class Player;
	class PlayerUpper : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			WALK,
			JUMP,
			WALKJUMP,
			
			FRONT_TO_UPSIDE,
			UPSIDE,
			UPSIDE_TO_FRONT,
			FRONT_TO_DOWNSIDE,
			DOWNSIDE,
			DOWNSIDE_TO_FRONT,

			SIT,

			SHOOT,
			SHOOT_UPSIDE,
			SHOOT_DOWNSIDE,
			SHOOT_SIT,

			KNIFE,
			BOMB,

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
		void Idle(eArms arms, bool bLeft);
		void Walk(eArms arms,bool bLeft);
		void Jump(eArms arms,bool bLeft, bool bJump);
		void WalkJump(eArms arms, bool bLeft, bool bJump);

		void FrontToUpside(eArms arms, bool bLeft);
		void Upside(eArms arms, bool bLeft);
		void UpsideToFront(eArms arms, bool bLeft);

		void FrontToDownside(eArms arms, bool bLeft);
		void Downside(eArms arms, bool bLeft);
		void DownsideToFront(eArms arms, bool bLeft);
		
		void Shoot(eArms arms, bool bLeft);
		void ShootUpside(eArms arms, bool bLeft);
		void ShootDownside(eArms arms, bool bLeft);
		
		void Knife(eArms arms, bool bLeft);
		void Bomb(eArms arms, bool bLeft);

	private:
		State mState;

		Image* mImage;
		Animator* mAnimator;
	};
}