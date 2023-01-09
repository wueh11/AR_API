#include "yaBombItem.h"

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
	BombItem::BombItem()
		: Item()
	{
		if (mImage == nullptr)
			mImage = Resources::Load<Image>(L"BombItem", L"..\\Resources\\Image\\Item\\bomb.bmp");
	}

	BombItem::~BombItem()
	{
	}

	void BombItem::Initialize()
	{
		Item::Initialize();

		SetSize({ (float)mImage->GetWidth(), (float)mImage->GetHeight() });
		SetScale({ M_SCALE, M_SCALE });
	}

	void BombItem::Tick()
	{
		Item::Tick();
	}

	void BombItem::Render(HDC hdc)
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

		Item::Render(hdc);
	}

	void BombItem::OnCollisionEnter(Collider* other)
	{
		Item::OnCollisionEnter(other);

		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;
		
		int count = player->GetInfo().bombCount;
		player->SetBombCount(count + 10);
	}

	void BombItem::OnCollisionStay(Collider* other)
	{
	}

	void BombItem::OnCollisionExit(Collider* other)
	{
	}
}