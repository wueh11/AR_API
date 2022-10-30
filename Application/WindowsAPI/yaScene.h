#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class GameObject;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize() = 0;
		virtual void Tick() = 0;
		virtual void Render(HDC hdc) = 0;

		virtual void Enter(); ///scene ���Խ� ����
		virtual void Exit();

		void AddGameObject(GameObject* object);

	private:
		std::vector<GameObject*> mObjects;
	};
}

