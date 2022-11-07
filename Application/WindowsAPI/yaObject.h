#pragma once
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaGameObject.h"

namespace ya
{
	namespace object
	{
		template <typename T>
		static __forceinline T* Instantiate(eColliderLayer type)
		{
			T* gameObject = new T();
			Scene* scene = SceneManager::GetPlayScene();
			scene->AddGameObject(dynamic_cast<GameObject*>(gameObject), type);

			return gameObject;
		}

		template <typename T>
		static __forceinline T* Instantiate(Vector2 position, eColliderLayer type)
		{
			T* gameObject = new T(position);
			Scene* scene = SceneManager::GetPlayScene();
			scene->AddGameObject(dynamic_cast<GameObject*>(gameObject), type);

			return gameObject;
		}

		static __forceinline void Destroy(GameObject* gameObj)
		{
			gameObj->Death();
		}

		// �ð� �����ؼ� �����
		static __forceinline void Destroy(GameObject* gameObj, float deathTime)
		{
			gameObj->SetDeathTime(deathTime);
		}

		static __forceinline void Release()
		{
			Scene* scene = SceneManager::GetPlayScene();
			std::vector<std::vector<GameObject*>> objects = scene->GetGameObject();

			for (size_t y = 0; y < _COLLIDER_LAYER; y++)
			{
				for (LayerObjects::iterator iter = objects[y].begin(); iter != objects[y].end(); ++iter)
				{
					if ((*iter)->IsDeath() == true)
					{
						iter = objects[y].erase(iter);
						continue;
					}

					++iter;
				}
			}
		}
	}
}