#pragma once
#include "yaGameObject.h"

// ¹ÖÄá°Ô
namespace ya
{
	class Image;
	class Animator;
	class Chewmein : public GameObject
	{
	public:
		Chewmein();
		~Chewmein();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		float mSpeed;
		Image* mImage;
		Animator* mAnimator;
	};
}

