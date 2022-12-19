#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class Player;
	class GameObject;
	class PixelImageObject;
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

		Player* GetPlayer() { return mPlayer; }
		void SetPlayer(Player* player) { mPlayer = player; }

	public:
		PixelImageObject* GetPixelImage() { return mPixelImage; }
		void SetPixelImage(PixelImageObject* pixelImage) { mPixelImage = pixelImage; }

	private:
		std::vector<std::vector<GameObject*>> mObjects;
		WindowData windowData;

		Player* mPlayer;
		PixelImageObject* mPixelImage;
	};

	typedef std::vector<std::vector<GameObject*>> GameObjects;
	typedef std::vector<GameObject*> LayerObjects;
}

