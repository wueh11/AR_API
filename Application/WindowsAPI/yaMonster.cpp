#include "yaMonster.h"

#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaImage.h"
#include "yaResources.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"

namespace ya
{
	Monster::Monster()
		: mSpeed(1.0f)
		, mTarget(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
	{
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		SetName(L"Monster");
		mCollider = new Collider();
		AddComponent(mCollider);
	}

	void Monster::Tick()
	{
		GameObject::Tick();
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc); /// 자식이 먼저그려져양함
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
		GameObject* object = other->GetOwner();

		if (object == nullptr)
			return;

		Vector2 otherPos = object->GetPos();
		Vector2 otherSize = object->GetSize();
		Vector2 otherScale = object->GetScale();

		Vector2 newPos = otherPos;

		if (GetPos().x <= otherPos.x)
			newPos.x = GetPos().x + (GetSize().x * GetScale().x / 2) + (otherSize.x * otherScale.x / 2) + 0.01f;
		else
			newPos.x = GetPos().x - (GetSize().x * GetScale().x / 2) - (otherSize.x * otherScale.x / 2) - 0.01f;

		object->SetPos(newPos);
	}

	void Monster::OnCollisionStay(Collider* other)
	{
	}

	void Monster::OnCollisionExit(Collider* other)
	{
	}
}