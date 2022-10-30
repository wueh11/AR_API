#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"

ya::LogoScene::LogoScene()
{
}

ya::LogoScene::~LogoScene()
{
}

void ya::LogoScene::Initialize()
{
	BgImageObject* bg = new BgImageObject();
	bg->SetImage(L"LogoBG", L"LogoBG.bmp");
	bg->Initialize();

	AddGameObject(bg);
}

void ya::LogoScene::Tick()
{
	//오브젝트 tick을 호출한다.
	Scene::Tick();

	if (KEY_DOWN(eKeyCode::N))
	{
		SceneManager::ChangeScene(eSceneType::Title);
	}
}

void ya::LogoScene::Render(HDC hdc)
{
	Scene::Render(hdc);

	Text text(hdc, L"Logo Scene", 10, 30);
}
