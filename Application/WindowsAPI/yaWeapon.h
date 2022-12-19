#pragma once
#include "yaItem.h"

namespace ya
{
	class Weapon : public Item
	{
	public:
		struct Info
		{
			std::wstring name = L"";
			UINT damage = 10;
		};

	public:
		Weapon();
		~Weapon();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	public:
		Info GetInfo() { return mInfo; }

	protected:
		Info mInfo;
	};
}

