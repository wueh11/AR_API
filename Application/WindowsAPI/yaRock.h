#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Rock : public GameObject
	{
	public:
		Rock();
		virtual ~Rock();

		virtual void Initialize() override;
		virtual void Tick();
		virtual void Render(HDC hdc);

		void SetSpeed(float speed) { mSpeed = speed; }

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		float mSpeed;
		float mAliveTime;
	};
}

