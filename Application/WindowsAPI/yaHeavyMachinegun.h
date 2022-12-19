#pragma once
#include "yaWeapon.h"

namespace ya
{
	class HeavyMachinegun : public Weapon
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

