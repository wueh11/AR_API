#pragma once
#include "yaGameObject.h"

namespace ya
{
	class HeavyMachinegun : public GameObject
	{
	public:
		HeavyMachinegun();
		virtual ~HeavyMachinegun();

		virtual void Initialize() override;
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:

	};
}

