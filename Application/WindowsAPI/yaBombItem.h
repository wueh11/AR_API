#pragma once
#include "yaItem.h"

namespace ya
{
	class BombItem : public Item
	{
	public:
		BombItem();
		virtual ~BombItem();

		virtual void Initialize() override;
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:

	};
}

