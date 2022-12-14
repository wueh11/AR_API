#include "yaHeavyMachinegun.h"

#include "yaCollider.h"
#include "yaPlayer.h"

namespace ya
{
	HeavyMachinegun::HeavyMachinegun()
	{
	}
	HeavyMachinegun::~HeavyMachinegun()
	{
	}
	void HeavyMachinegun::Initialize()
	{
	}
	void HeavyMachinegun::Tick()
	{
		GameObject::Tick();
	}
	void HeavyMachinegun::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HeavyMachinegun::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		player->PickupArms(eArms::HeavyMachinegun, 200);
		this->Death();
	}
	void HeavyMachinegun::OnCollisionStay(Collider* other)
	{
	}
	void HeavyMachinegun::OnCollisionExit(Collider* other)
	{
	}
}