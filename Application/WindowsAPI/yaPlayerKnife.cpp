#include "yaPlayerKnife.h"

#include "yaPlayerKnife.h"

#include "yaMonster.h"
#include "yaChewmein.h"
#include "yaCollider.h"
#include "yaTime.h"

#include "yaPlayer.h"

namespace ya
{
	PlayerKnife::PlayerKnife()
		: mTime(0.0f)
		, mAliveTime(0.2f)
	{
		SetSize({ 20.0f, 30.0f });
		SetScale({ M_SCALE, M_SCALE });
		Collider* collider = AddComponent<Collider>();
	}

	PlayerKnife::~PlayerKnife()
	{
	}

	void PlayerKnife::Initialize()
	{

	}

	void PlayerKnife::Tick()
	{
		GameObject::Tick();

		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			Death();
		}

		Chewmein* owner = dynamic_cast<Chewmein*>(GetOwner());
		if (owner == nullptr)
			return;

		if (owner->GetMoveState().bLeft)
			SetOffset({ -70.0f,  0.0f });
		else
			SetOffset({ 70.0f,  0.0f });
		Vector2 pos = owner->GetPos() + GetOffset();
		Vector2 size = GetSize();
		SetPos(pos);
	}

	void PlayerKnife::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerKnife::OnCollisionEnter(Collider* other)
	{
		Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
		if (monster == nullptr)
			return;
		monster->SetHp(-40);
	}

	void PlayerKnife::OnCollisionStay(Collider* other)
	{
	}

	void PlayerKnife::OnCollisionExit(Collider* other)
	{
	}
}