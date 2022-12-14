#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class Player;
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

		void AddGameObject(GameObject* object, eColliderLayer type);

		std::vector<GameObject*>& GetGameObjects(eColliderLayer type) { return mObjects[(UINT)type]; }
		std::vector<std::vector<GameObject*>>& GetGameObject() { return mObjects; }

		Player* GetPlayer() { return mPlayer; }
		void SetPlayer(Player* player) { mPlayer = player; }
		
		bool IsActive() { return mbActive; }

		bool mbActive;
	private:
		std::vector<std::vector<GameObject*>> mObjects;
		WindowData windowData;

		Player* mPlayer;
	};

	typedef std::vector<std::vector<GameObject*>> GameObjects;
	typedef std::vector<GameObject*> LayerObjects;
}

