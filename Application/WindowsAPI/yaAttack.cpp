#include "yaAttack.h"

#include "yaChewmein.h"
#include "yaCollider.h"
#include "yaTime.h"

namespace ya
{
	Attack::Attack()
		: mTime(0.0f)
	{
		/*SetPos(Vector2::Zero);
		SetScale(Vector2::One);
		SetSize(Vector2::Zero);*/
	}

	Attack::~Attack()
	{
	}

	void Attack::Initialize()
	{
		GameObject* owner = GetOwner();
		SetScale(owner->GetScale());
		SetSize({ 70.0f, 50.0f });
		SetPos(owner->GetPos());
		SetOffset({ 0.0f, 0.0f });

		Collider* collider = new Collider();
		collider->SetPos(GetPos());
		collider->SetSize(GetSize());
		AddComponent(collider);
	}

	void Attack::Tick()
	{
		GameObject::Tick();

		GameObject* owner = GetOwner();
		if (owner == nullptr)
			return;

		Vector2 pos = owner->GetPos() + GetOffset();
		Vector2 size = GetSize();
		SetPos(pos);
	}

	void Attack::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Attack::OnCollisionEnter(Collider* other)
	{
	}

	void Attack::OnCollisionStay(Collider* other)
	{
	}

	void Attack::OnCollisionExit(Collider* other)
	{
	}
}