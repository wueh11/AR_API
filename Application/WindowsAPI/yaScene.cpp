#include "yaScene.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"

namespace ya
{
	Scene::Scene()
	{
		SceneManager::SetPlayScene(this);
		mObjects.resize(_COLLIDER_LAYER);
	}

	Scene::~Scene()
	{
		for (size_t j = 0; j < _COLLIDER_LAYER; j++)
		{
			for (size_t i = 0; i < mObjects[j].size(); i++)
			{
				delete mObjects[j][i];
				mObjects[j][i] = nullptr;
			}
		}
	}

	void Scene::Initialize()
	{
		for (size_t j = 0; j < _COLLIDER_LAYER; j++)
		{
			for (size_t i = 0; i < mObjects[j].size(); i++)
			{
				if (mObjects[j][i] == nullptr)
					continue;

				if (mObjects[j][i]->IsDeath())
					continue;

				mObjects[j][i]->Initialize();
			}
		}
	}

	void Scene::Tick()
	{
		for (size_t j = 0; j < _COLLIDER_LAYER; j++)
		{
			for (size_t i = 0; i < mObjects[j].size(); i++)
			{
				if (mObjects[j][i] == nullptr)
					continue;
				if (mObjects[j][i]->IsDeath())
					continue;

				mObjects[j][i]->Tick();
			}
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (size_t j = 0; j < _COLLIDER_LAYER; j++)
		{
			for (size_t i = 0; i < mObjects[j].size(); i++)
			{
				if (mObjects[j][i] == nullptr)
					continue;
				if (mObjects[j][i]->IsDeath())
					continue;

				mObjects[j][i]->Render(hdc);
			}
		}
	}

	void Scene::Enter()
	{
	}

	void Scene::Exit()
	{
	}

	void Scene::AddGameObject(GameObject* object, eColliderLayer type)
	{
		if (object == nullptr)
			return;

		mObjects[(UINT)type].push_back(object);
	}
}