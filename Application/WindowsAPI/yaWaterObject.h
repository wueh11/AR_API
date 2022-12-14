#pragma once
#include "yaGameObject.h"
#include "yaWaterEffect.h"

namespace ya
{
	class Collider;
	class WaterObject : public GameObject
	{
	public:
		WaterObject();
		~WaterObject();

		// GameObject��(��) ���� ��ӵ�
		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Collider* mCollider;
		WaterEffect* mWaterEffect;
	};
}

