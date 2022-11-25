#include "yaMission1Scene.h"
#include "yaInput.h"

#include "yaCollisionManager.h"
#include "yaSceneManager.h"

#include "yaImageObject.h"
#include "yaPixelImageObject.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaObject.h"
#include "yaChewmein.h"
#include "yaApplication.h"

namespace ya
{
	Mission1Scene::Mission1Scene()
	{
	}

	Mission1Scene::~Mission1Scene()
	{
	}

	void Mission1Scene::Initialize()
	{
		Player* player = ya::object::Instantiate<Player>(eColliderLayer::Player);
		SetPlayer(player);
		
		WindowData windowData = Application::GetInstance().GetWindowData();

		/*ImageObject* Background = new ImageObject();
		Background->SetScale({ M_SCALE, M_SCALE });
		Background->SetImage(L"Mission1_part1_background", L"Background\\part1\\background.bmp");
		Background->Initialize();
		Background->SetPos({ 0.0f, -64.0f * M_SCALE });
		AddGameObject(Background, eColliderLayer::Background);*/

		PixelImageObject* BackgroundPixel = new PixelImageObject();
		//BackgroundPixel->SetScale({ M_SCALE, M_SCALE });
		BackgroundPixel->SetImage(L"Mission1_part1_background_pixel", L"Background\\part1\\background_pixel.bmp");
		BackgroundPixel->Initialize();
		BackgroundPixel->SetPos({ 0.0f, 0.0f});
		//BackgroundPixel->SetPos({ 0.0f, windowData.height - (BackgroundPixel->GetSize().y * BackgroundPixel->GetScale().y)});
		AddGameObject(BackgroundPixel, eColliderLayer::Background_pixel);


		/*ImageObject* BackgroundObject = new ImageObject();
		BackgroundObject->SetImage(L"Mission1_part1_backobject", L"Background\\part1\\background_object.bmp");
		BackgroundObject->Initialize();
		BackgroundObject->SetPos({ 0.0f, 00.0f });
		BackgroundObject->SetScale({ M_SCALE, M_SCALE });
		AddGameObject(BackgroundObject, eColliderLayer::Background);*/

		
		//ya::object::Instantiate<Chewmein>(eColliderLayer::Monster);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
	}

	void Mission1Scene::Tick()
	{
		Scene::Tick();
	}

	void Mission1Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//Text text(hdc, L"Mission1", 10, 30);
	}

	void Mission1Scene::Enter()
	{
	}

	void Mission1Scene::Exit()
	{
	}
}