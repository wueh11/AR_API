#include "yaPlayerKnifeSight.h"

#include "yaChewmein.h"
#include "yaCollider.h"
#include "yaTime.h"

#include "yaPlayer.h"

namespace ya
{
	PlayerKnifeSight::PlayerKnifeSight()
		: mbActive(false)
	{
		SetSize({ 20.0f, 24.0f });
		SetScale({ M_SCALE, M_SCALE });
	}

	PlayerKnifeSight::~PlayerKnifeSight()
	{
	}

	void PlayerKnifeSight::Initialize()
	{
		AddComponent<Collider>();
	}

	void PlayerKnifeSight::Tick()
	{
		GameObject::Tick();

		Player* owner = dynamic_cast<Player*>(GetOwner());
		if (owner == nullptr)
			return;

		if (owner->GetMoveState().bLeft)
			SetOffset({ -60.0f,  0.0f });
		else
			SetOffset({ 60.0f,  0.0f });

		Vector2 pos = owner->GetPos() + GetOffset();
		Vector2 size = GetSize();
		SetPos(pos);
	}

	void PlayerKnifeSight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerKnifeSight::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		if (player == nullptr)
			return;

		player->SetKnife(true);
	}

	void PlayerKnifeSight::OnCollisionStay(Collider* other)
	{
	}

	void PlayerKnifeSight::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		if (player == nullptr)
			return;

		player->SetKnife(false);
		//player->GetMoveState().SetKnife(false);
	}
}