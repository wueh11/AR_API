#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"

namespace ya
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		//¹è°æ
		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"PlayBG", L"PlayBG.bmp");
		bg->Initialize();

		AddGameObject(bg);

		// player
		AddGameObject(new Player());
	}

	void PlayScene::Tick()
	{
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::End);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		Text text(hdc, L"Play Scene", 10, 30);
	}

	void PlayScene::Enter()
	{
	}

	void PlayScene::Exit()
	{
	}
}