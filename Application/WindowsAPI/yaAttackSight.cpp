#include "yaAttackSight.h"
#include "yaChewmein.h"
#include "yaCollider.h"
#include "yaTime.h"

namespace ya
{
	AttackSight::AttackSight()
		: mTime(0.0f)
	{
		/*SetPos(Vector2::Zero);
		SetScale(Vector2::One);
		SetSize(Vector2::Zero);*/
	}

	AttackSight::~AttackSight()
	{
	}

	void AttackSight::Initialize()
	{
		GameObject* owner = GetOwner();
		SetScale(owner->GetScale());
		SetSize({ 70.0f, 50.0f });
		SetPos(owner->GetPos());
		SetOffset({ 0.0f, 0.0f });

		Collider* collider = new Collider();
		collider->SetPos(GetPos());
		collider->SetSize(GetSize());
		//collider->SetOffset({ 0.0f, 20.0f });
		AddComponent(collider);
	}

	void AttackSight::Tick()
	{
		GameObject::Tick();

		GameObject* owner = GetOwner();
		if (owner == nullptr)
			return;

		Vector2 pos = owner->GetPos() + GetOffset();
		Vector2 size = GetSize();
		SetPos(pos);
	}

	void AttackSight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void AttackSight::OnCollisionEnter(Collider* other)
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

		//if(owner->GetState() == ya::Chewmein::eState::IDLE)

		if (math::Random(0, 2) % 2 == 0)
			owner->SetState(ya::Chewmein::eState::ATTACK);
		else
			owner->SetState(ya::Chewmein::eState::WALK_BACK);
	}

	void AttackSight::OnCollisionStay(Collider* other)
	{
		mTime += 1.0f * Time::DeltaTime();

		if (mTime > 2.0f)
		{
			mTime = 0.0f;

			Chewmein* owner = dynamic_cast<Chewmein*> (GetOwner());
			if (math::Random(0, 2) % 2 == 0)
				owner->SetState(ya::Chewmein::eState::ATTACK);
			else
				owner->SetState(ya::Chewmein::eState::WALK_BACK);
		}
	}

	void AttackSight::OnCollisionExit(Collider* other)
	{
		/*Chewmein* owner = dynamic_cast<Chewmein*> (GetOwner());
		GameObject* target = other->GetOwner();

		if (target == nullptr)
			return;

		if (owner->GetTarget().pTarget == nullptr)
			return;
		else
			owner->SetTarget(target);

		Vector2 ownerPos = owner->GetPos();
		Vector2 targetPos = target->GetPos();

		owner->SetLeft(ownerPos.x >= targetPos.x);
		owner->SetState(ya::Chewmein::eState::IDLE);*/
	}
}