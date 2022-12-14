#include "yaEyeSight.h"
#include "yaChewmein.h"

#include "yaCollider.h"
#include "yaTime.h"

namespace ya
{
	EyeSight::EyeSight()
		: mTime(0.0f)
	{
		/*SetPos(Vector2::Zero);
		SetScale(Vector2::One);
		SetSize(Vector2::Zero);*/
	}

	EyeSight::~EyeSight()
	{
	}

	void EyeSight::Initialize()
	{
		GameObject* owner = GetOwner();
		SetScale(owner->GetScale());
		SetSize({ 300.0f, 50.0f });
		SetPos(owner->GetPos());
		SetOffset({ 0.0f, 0.0f });

		Collider* collider = new Collider();
		collider->SetPos(GetPos());
		collider->SetSize(GetSize());
		//collider->SetOffset({ 0.0f, 20.0f });
		AddComponent(collider);
	}

	void EyeSight::Tick()
	{
		GameObject::Tick();

		GameObject* owner = GetOwner();
		if (owner == nullptr)
			return;

		Vector2 pos = owner->GetPos() + GetOffset();
		Vector2 size = GetSize();
		SetPos(pos);
	}

	void EyeSight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void EyeSight::OnCollisionEnter(Collider* other)
	{
		Chewmein* owner = dynamic_cast<Chewmein*> (GetOwner());
		GameObject* target = other->GetOwner();

		if (target == nullptr)
			return;

		if (owner->GetTarget() == nullptr)
			owner->SetTarget(target);

		Vector2 ownerPos = owner->GetPos();
		Vector2 targetPos = target->GetPos();
		
		owner->SetLeft(ownerPos.x >= targetPos.x);
		
		if (math::Random(0, 2) % 2 == 0)
			owner->SetState(ya::Chewmein::eState::WALK_FRONT);
		else
			owner->SetState(ya::Chewmein::eState::ATTACK_BUBBLE);
	}

	void EyeSight::OnCollisionStay(Collider* other)
	{
		/*mTime += 1.0f * Time::DeltaTime();

		if (mTime > 5.0f)
		{
			mTime = 0.0f;

			Chewmein* owner = dynamic_cast<Chewmein*> (GetOwner());
			owner->SetState(ya::Chewmein::eState::WALK_FRONT);
		}*/
	}

	void EyeSight::OnCollisionExit(Collider* other)
	{
		/*Chewmein* owner = dynamic_cast<Chewmein*> (GetOwner());
		owner->SetState(ya::Chewmein::eState::IDLE);*/
	}
}