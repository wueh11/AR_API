#pragma once
#include "yaEntity.h"
#include "Common.h"

namespace ya
{
	class GameObject;
	class Component : public Entity
	{
	public:
		friend class GameObject;

		Component(eComponentType type);
		Component() = delete; /// 기본생성자 막음
		virtual ~Component();

		virtual void Tick() = 0;
		virtual void Render(HDC hdc);

		GameObject* GetOwner() { return mOwner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}