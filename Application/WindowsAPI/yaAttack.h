#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Attack : public GameObject
	{
	public:
		Attack();
		~Attack();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		float mTime;
	};
}

