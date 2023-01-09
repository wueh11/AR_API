#include "yaSceneManager.h"
#include "yaLogoScene.h"
#include "yaTitleScene.h"
#include "yaPlayScene.h"
#include "yaMission1Scene.h"
#include "yaEndScene.h"
#include "yaCharacterSelectScene.h"
#include "yaInput.h"

#include "yaObject.h"
#include "yaCollisionManager.h"

namespace ya
{
	//전역변수 초기화
	Scene* SceneManager::mScenes[(UINT)eSceneType::MAX];
	Scene* SceneManager::mPlayScene = nullptr;
	eSceneType SceneManager::mType = eSceneType::MAX;

	void SceneManager::Initialize()
	{
		// 모든 씬들을 초기화
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Logo]->Initialize();

		mScenes[(UINT)eSceneType::Select] = new CharacterSelectScene();
		mScenes[(UINT)eSceneType::Select]->Initialize();

		mScenes[(UINT)eSceneType::Mission1] = new Mission1Scene();
		mScenes[(UINT)eSceneType::Mission1]->Initialize();

		mScenes[(UINT)eSceneType::End] = new EndScene();
		mScenes[(UINT)eSceneType::End]->Initialize();

		ChangeScene(eSceneType::Logo);
	}

	void SceneManager::Tick()
	{
		if (GetFocus())
		{
			if (KEY_DOWN(eKeyCode::N))
			{
				if (mType != eSceneType::MAX)
				{
					eSceneType type = (eSceneType)((UINT)mType + 1);
					SceneManager::ChangeScene(type);
				}
			}
		}

		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		mPlayScene->Render(hdc);
	}

	void SceneManager::DestroyGameObject()
	{
		ya::object::Release();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::ChangeScene(eSceneType type)
	{ 
		if (mScenes[(UINT)type] == nullptr)
			return;

		mType = type;

		CollisionManager::Clear();
		mPlayScene->Exit();
		mPlayScene = mScenes[(UINT)type];

		mPlayScene->Enter();
	}
}