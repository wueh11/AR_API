#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Effect : public GameObject
	{
	public:
		Effect();
		~Effect();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		/*virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);*/

	private:
		float mSpeed;
		float mAliveTime;
		Image* mImage;
	};
}
