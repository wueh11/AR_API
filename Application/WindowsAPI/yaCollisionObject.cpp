#include "yaCollisionObject.h"

#include "yaCollider.h"

#include "yaPlayer.h"

namespace ya
{
	CollisionObject::CollisionObject()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
	{	
		SetName(L"CollisionObject");
		SetPos({ Vector2::Zero });
		SetScale(Vector2::One);
		SetSize({ 100.0f, 100.0f });
	}

	CollisionObject::~CollisionObject()
	{
	}

	void CollisionObject::Initialize()
	{
		mCollider = AddComponent<Collider>();
	}

	void CollisionObject::Tick()
	{
		GameObject::Tick();
	}

	void CollisionObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void CollisionObject::OnCollisionEnter(Collider* other)
	{
	}

	void CollisionObject::OnCollisionStay(Collider* other)
	{
	}

	void CollisionObject::OnCollisionExit(Collider* other)
	{
	}
}