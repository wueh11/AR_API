#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Animator;
	class WaterEffect : public GameObject
	{
	public:
		enum class eState
		{
			DEFAULT,
			WALK,
			JUMP,
			FALL,
		};

	public:
		WaterEffect();
		~WaterEffect();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	public:
		void SetState(eState state) { mState = state; }

		void SetShow(bool show) { mbShow = show; }
		void Show() { mbShow = true; }
		void Hide() { mbShow = false; }

	private:
		void Defalut();
		void Walk();
		void Jump();
		void Fall();

	private:
		Image* mImage;
		Animator* mAnimator;

		eState mState;
		bool mbShow;
	};
}

