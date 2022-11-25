#include "yaEndScene.h"
#include "yaPlayer.h"

namespace ya
{
	EndScene::EndScene()
	{
	}
	EndScene::~EndScene()
	{
	}
	void EndScene::Initialize()
	{
		/*BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"EndBG", L"EndBG.bmp");
		bg->Initialize();

		AddGameObject(bg, eColliderLayer::Background);*/
	}
	void EndScene::Tick()
	{
		Scene::Tick();
	}
	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Text text(hdc, L"End Scene", 10, 30);
	}
	void EndScene::Enter()
	{
	}
	void EndScene::Exit()
	{
	}
}