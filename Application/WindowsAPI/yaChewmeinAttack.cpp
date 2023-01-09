#include "yaChewmeinAttack.h"

#include "yaChewmein.h"
#include "yaCollider.h"
#include "yaTime.h"

#include "yaPlayer.h"

namespace ya
{
	ChewmeinAttack::ChewmeinAttack()
		: mTime(0.0f)
		, mAliveTime(0.5f)
	{
		SetSize({ 20.0f, 30.0f });
		SetScale({ M_SCALE, M_SCALE });

		Collider* collider = AddComponent<Collider>();
		collider->SetActive(false);
	}

	ChewmeinAttack::~ChewmeinAttack()
	{
	}

	void ChewmeinAttack::Initialize()
	{
		
	}

	void ChewmeinAttack::Tick()
	{
		GameObject::Tick();

		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			Death();
		}

		if (Time::Timer(L"chewmein_attack_" + std::to_wstring((UINT32)this), 0.2f))
		{
			Collider* collider = GetComponent<Collider>();
			collider->SetActive(true);
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

	void ChewmeinAttack::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ChewmeinAttack::OnCollisionEnter(Collider* other)
	{
		/*Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;
		player->Die();*/
	}

	void ChewmeinAttack::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;
		player->Attacked();
	}

	void ChewmeinAttack::OnCollisionExit(Collider* other)
	{
	}
}