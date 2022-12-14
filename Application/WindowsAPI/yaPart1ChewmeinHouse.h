#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Collider;
	class Part1ChewmeinHouse : public GameObject
	{
	public:
		Part1ChewmeinHouse();
		~Part1ChewmeinHouse();

		// GameObject��(��) ���� ��ӵ�
		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Collider* mCollider;
	};
}

