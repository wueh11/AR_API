#include "yaTitleScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaApplication.h"

namespace ya
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"TitleBG", L"TitleBG.bmp");

		AddGameObject(bg, eColliderLayer::Background);
	}
	void TitleScene::Tick()
	{
		Scene::Tick();

		/*if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Play);
		}*/
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Text text(hdc, L"Title Scene", 10, 30);
	}
	void TitleScene::Enter()
	{
	}
	void TitleScene::Exit()
	{
	}
}