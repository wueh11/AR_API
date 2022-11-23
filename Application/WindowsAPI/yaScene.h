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

		virtual void Enter(); ///scene 진입시 동작
		virtual void Exit();

		void AddGameObject(GameObject* object, eColliderLayer type);

		std::vector<GameObject*>& GetGameObjects(eColliderLayer type) { return mObjects[(UINT)type]; }
		std::vector<std::vector<GameObject*>>& GetGameObject() { return mObjects; }


	private:
		std::vector<std::vector<GameObject*>> mObjects;
		WindowData windowData;
	};

	typedef std::vector<std::vector<GameObject*>> GameObjects;
	typedef std::vector<GameObject*> LayerObjects;
}

