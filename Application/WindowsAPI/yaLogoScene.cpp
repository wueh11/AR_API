#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaImageObject.h"
#include "yaApplication.h"

namespace ya
{
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{
		mBackground = Image::Create(L"LogoBg", 1600, 900);

		float width = (float)Application::GetInstance().GetWindowData().width;
		float height = (float)Application::GetInstance().GetWindowData().height;

		ImageObject* title = new ImageObject();
		title->SetImage(L"Title", L"title.bmp");
		title->SetPos({ (width / 2.0f) - (title->GetSize().x / 2.0f), 100.0f});

		AddGameObject(title, eColliderLayer::Default);
	}

	void LogoScene::Tick()
	{
		Scene::Tick();

	}

	void LogoScene::Render(HDC hdc)
	{
		{//¹è°æ
			Vector2 rect;
			rect.x = Application::GetInstance().GetWindowData().width;
			rect.y = Application::GetInstance().GetWindowData().height;

			TransparentBlt(hdc, 0, 0
				, rect.x, rect.y, mBackground->GetDC()
				, 0, 0, mBackground->GetWidth(), mBackground->GetHeight()
				, RGB(255, 0, 255));
		}

		Scene::Render(hdc);

		Text text(hdc, L"Logo Scene", 10, 30);
	}

	void LogoScene::Enter()
	{
	}

	void LogoScene::Exit()
	{
	}
}