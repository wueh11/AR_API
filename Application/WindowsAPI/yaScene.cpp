#include "yaScene.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaApplication.h"

namespace ya
{
	Scene::Scene()
		: mPlayer(nullptr)
		, mbActive(false)
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
		WindowData windowData = Application::GetInstance().GetWindowData();

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

				/// 카메라 밖에있는 오브젝트들 렌더 X
				/*Vector2 pos = mObjects[j][i]->GetPos();
				pos = Camera::CalculatePos(pos);

				if (pos.x < -100 || pos.y < -100)
					continue;
				if (pos.x > windowData.width + 100 || pos.y > windowData.height + 100)
					continue;*/

				mObjects[j][i]->Render(hdc);
			}
		}
	}

	void Scene::Enter()
	{
		mbActive = true;
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