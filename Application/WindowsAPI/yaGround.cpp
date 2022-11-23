#include "yaGround.h"
#include "yaPlayer.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

namespace ya
{
	Ground::Ground()
	{
		Collider* coliider = AddComponent<Collider>();
		coliider->SetScale(Vector2(600.0f, 30.0f));
	}

	Ground::~Ground()
	{
	}

	void Ground::Tick()
	{
		GameObject::Tick();
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		Player* playerObj = dynamic_cast<Player*>(other->GetOwner());
		playerObj->GetComponent<Rigidbody>()->SetGround(true);

		/*int hp = playerObj->GetHp();
		hp -= 10;
		playerObj->SetHp(hp);*/

		/// 충돌 위치보다 더 내려가는 경우 위치를 보정해준다.
		float fLen = fabs(other->GetPos().y - GetComponent<Collider>()->GetPos().y);
		float fScale = other->GetScale().y / 2.0f + GetComponent<Collider>()->GetScale().y / 2.0f;

		if (fLen < fScale)
		{
			Vector2 playerPos = playerObj->GetPos();
			playerPos.y -= (fScale - fLen) - 1.0f;
			playerObj->SetPos(playerPos);
		}
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}

	void Ground::OnCollisionExit(Collider* other)
	{
		GameObject* playerObj = other->GetOwner();
		playerObj->GetComponent<Rigidbody>()->SetGround(false);
	}
}