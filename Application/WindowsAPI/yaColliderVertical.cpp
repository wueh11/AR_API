#include "yaColliderVertical.h"

#include "yaCollider.h"
#include "yaRigidbody.h"
#include "yaPlayer.h"

namespace ya
{
	ColliderVertical::ColliderVertical()
		: mCollider(nullptr)
	{
		SetName(L"ColliderVertical");
	}

	ColliderVertical::~ColliderVertical()
	{
	}

	void ColliderVertical::Initialize()
	{
		GameObject* owner = GetOwner();
		SetPos(owner->GetPos());
		SetSize({ owner->GetSize().x / 2.0f, owner->GetSize().y });
		SetScale(owner->GetScale());

		if (owner == nullptr)
			return;

		mCollider = AddComponent<Collider>();
	}

	void ColliderVertical::Tick()
	{
		GameObject::Tick();

		Player* player = dynamic_cast<Player*>(GetOwner());
		Vector2 pos = player->GetPos() + GetOffset();
		SetPos(pos);
	}

	void ColliderVertical::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ColliderVertical::OnCollisionEnter(Collider* other)
	{
		GameObject* owner = GetOwner();
		owner->GetComponent<Rigidbody>()->SetPixel(false);
		owner->GetComponent<Rigidbody>()->SetGround(true);

		if (owner == nullptr)
			return;

		Collider* collider = GetComponent<Collider>();

		Vector2 otherPos = other->GetPos();
		Vector2 otherSize = other->GetSize();
		Vector2 otherScale = other->GetScale();

		float fLen = fabs(otherPos.y - collider->GetPos().y);
		float fScale = otherSize.y * otherScale.y / 2.0f + collider->GetSize().y * collider->GetScale().y / 2.0f;

		if (fLen < fScale)
		{
			Vector2 newPos = owner->GetPos();
			newPos.y += (fScale - fLen) - 0.5f;
			owner->SetPos(newPos);
		}
	}

	void ColliderVertical::OnCollisionStay(Collider* other)
	{
	}

	void ColliderVertical::OnCollisionExit(Collider* other)
	{
		GameObject* owner = GetOwner();
		owner->GetComponent<Rigidbody>()->SetGround(false);
		owner->GetComponent<Rigidbody>()->SetPixel(true);
	}
}