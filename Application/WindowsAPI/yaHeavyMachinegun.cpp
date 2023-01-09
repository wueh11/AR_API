#include "yaHeavyMachinegun.h"

#include "yaCamera.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

#include "yaPlayer.h"

#include "yaItemEffect.h"

#include "yaSceneManager.h"
#include "yaScene.h"

namespace ya
{
	HeavyMachinegun::HeavyMachinegun()
		: Weapon()
	{
		if (mImage == nullptr)
			mImage = Resources::Load<Image>(L"heavymachinegun", L"..\\Resources\\Image\\Item\\heavymachinegun.bmp");
	}

	HeavyMachinegun::~HeavyMachinegun()
	{
	}

	void HeavyMachinegun::Initialize()
	{
		Weapon::Initialize();

		SetSize({ (float)mImage->GetWidth(), (float)mImage->GetHeight() });
		SetScale({ M_SCALE, M_SCALE});
	}

	void HeavyMachinegun::Tick()
	{
		Weapon::Tick();
	}

	void HeavyMachinegun::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 size = GetSize();

		Vector2 rect;
		rect.x = mImage->GetWidth();
		rect.y = mImage->GetHeight();

		pos = Camera::CalculatePos(pos);

		TransparentBlt(hdc, pos.x - (size.x * scale.x / 2), pos.y - (size.y * scale.y / 2)
			, rect.x * scale.x, rect.y * scale.y, mImage->GetDC()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		Weapon::Render(hdc);
	}

	void HeavyMachinegun::OnCollisionEnter(Collider* other)
	{
		Weapon::OnCollisionEnter(other);

		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		player->PickupArms(eArms::HeavyMachinegun, 200);
	}

	void HeavyMachinegun::OnCollisionStay(Collider* other)
	{
	}

	void HeavyMachinegun::OnCollisionExit(Collider* other)
	{
	}
}