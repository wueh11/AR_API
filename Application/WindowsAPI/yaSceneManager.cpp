#include "yaSceneManager.h"
#include "yaLogoScene.h"
#include "yaTitleScene.h"
#include "yaPlayScene.h"
#include "yaEndScene.h"

namespace ya
{
	//전역변수 초기화
	Scene* SceneManager::mScenes[(UINT)eSceneType::MAX];
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		// 모든 씬들을 초기화
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Logo]->Initialize();
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Title]->Initialize();

		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Play]->Initialize();
		mScenes[(UINT)eSceneType::End] = new EndScene();
		mScenes[(UINT)eSceneType::End]->Initialize();
		mPlayScene = mScenes[(UINT)eSceneType::Logo];

		ChangeScene(eSceneType::Logo);
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		mPlayScene->Render(hdc);
	}

	void SceneManager::DestroyGameObject()
	{
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
		{
			return;
		}

		mPlayScene->Exit();
		mPlayScene = mScenes[(UINT)type];

		mPlayScene->Enter();
	}
}