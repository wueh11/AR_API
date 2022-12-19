#include "yaWeapon.h"

namespace ya
{
	Weapon::Weapon()
	{
	}
	Weapon::~Weapon()
	{
	}
	void Weapon::Initialize()
	{
	}
	void Weapon::Tick()
	{
		Item::Tick();
	}
	void Weapon::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void Weapon::OnCollisionEnter(Collider* other)
	{
		Item::OnCollisionEnter(other);
	}
	void Weapon::OnCollisionStay(Collider* other)
	{
	}
	void Weapon::OnCollisionExit(Collider* other)
	{
	}
}