#include "yaColliderHorizontal.h"

#include "yaCollider.h"
#include "yaPlayer.h"

namespace ya
{
	ColliderHorizontal::ColliderHorizontal()
		: mCollider(nullptr)
	{
		SetName(L"ColliderHorizontal");
	}
	ColliderHorizontal::~ColliderHorizontal()
	{
	}

	void ColliderHorizontal::Initialize()
	{
		GameObject* owner = GetOwner();
		SetPos(owner->GetPos());
		SetSize({ owner->GetSize().x, owner->GetSize().y / 2.0f });
		SetScale(owner->GetScale());

		if (owner == nullptr)
			return;

		mCollider = AddComponent<Collider>();
	}

	void ColliderHorizontal::Tick()
	{
		GameObject::Tick();

		GameObject* owner = GetOwner();
		Vector2 pos = owner->GetPos() + GetOffset();
		SetPos(pos);
	}

	void ColliderHorizontal::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ColliderHorizontal::OnCollisionEnter(Collider* other)
	{
		GameObject* owner = GetOwner();

		if (owner == nullptr)
			return;

		Collider* collider = GetComponent<Collider>();

		Vector2 otherPos = other->GetPos();
		Vector2 otherSize = other->GetSize();
		Vector2 otherScale = other->GetScale();

		float fLen = fabs(otherPos.x - collider->GetPos().x);
		float fScale = otherSize.x * otherScale.x / 2.0f + collider->GetSize().x * collider->GetScale().x / 2.0f;

		if (fLen < fScale)
		{
			Vector2 newPos = owner->GetPos();

			if (collider->GetPos().x >= otherPos.x)
				newPos.x += (fScale - fLen) + 2.0f;
			else
				newPos.x -= (fScale - fLen) + 2.0f;

			owner->SetPos(newPos);
		}
	}

	void ColliderHorizontal::OnCollisionStay(Collider* other)
	{
	}

	void ColliderHorizontal::OnCollisionExit(Collider* other)
	{
	}
}