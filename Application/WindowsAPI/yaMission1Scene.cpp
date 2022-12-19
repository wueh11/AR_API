#include "yaMission1Scene.h"

#include "yaApplication.h"
#include "yaInput.h"
#include "yaCamera.h"
#include "yaObject.h"

#include "yaCollisionManager.h"
#include "yaSceneManager.h"

#include "yaPlayer.h"
#include "yaImageObject.h"
#include "yaBgImageObject.h"
#include "yaPixelImageObject.h"
#include "yaCollisionObject.h"

#include "yaMonster.h"
#include "yaChewmein.h"
#include "yaCameraWall.h"
#include "yaPart1ChewmeinHouse.h"

#include "yaWaterObject.h"
#include "yaWaterBackground.h"
#include "yaWaterFront.h"

#include "yaHeavyMachinegun.h"

namespace ya
{
	Mission1Scene::Mission1Scene()
		: mPixelObject(nullptr)
	{
	}

	Mission1Scene::~Mission1Scene()
	{
	}

	void Mission1Scene::Initialize()
	{
		Player* player = ya::object::Instantiate<Player>(eColliderLayer::Player);
		SetPlayer(player);
		Camera::SetTarget(player);
		
		WindowData windowData = Application::GetInstance().GetWindowData();

		BgImageObject* background = ya::object::Instantiate<BgImageObject>(eColliderLayer::Background);
		background->SetImage(L"Mission1_part1_background", L"Background\\part1\\2.7\\background.bmp");
		background->SetPos({ 0.0f, -176.0f });

		ImageObject* backgroundObject = ya::object::Instantiate<ImageObject>(eColliderLayer::Background);
		backgroundObject->SetImage(L"Mission1_part1_backobject", L"Background\\part1\\2.7\\background_object.bmp");
		backgroundObject->SetPos({ 0.0f, -10.0f });

		PixelImageObject* backgroundPixel = ya::object::Instantiate<PixelImageObject>(eColliderLayer::Background_pixel);
		backgroundPixel->SetImage(L"Mission1_part1_background_pixel", L"Background\\part1\\2.7\\background_pixel.bmp");
		backgroundPixel->SetPos({ 0.0f, -10.0f });
		backgroundPixel->AddObject(player);
		SetPixelImage(backgroundPixel);

		Vector2 bgObjectPos = backgroundPixel->GetPos();

		{ // object

			WaterObject* waterObject = ya::object::Instantiate<WaterObject>(eColliderLayer::Event);
			
			WaterBackground* waterBackground = ya::object::Instantiate<WaterBackground>(eColliderLayer::Background);
			waterBackground->SetPos({ bgObjectPos.x + 710.0f, bgObjectPos.y + 431.0f + 35.0f });
			WaterFront* waterFront = ya::object::Instantiate<WaterFront>(eColliderLayer::Background_front);
			waterFront->SetPos({ bgObjectPos.x + 710.0f, bgObjectPos.y + 494.0f + 55.0f });

			ImageObject* deadfish1 = ya::object::Instantiate<ImageObject>(eColliderLayer::Background);
			deadfish1->SetImage(L"Mission1_part1_deadfish1", L"Background\\part1\\2.7\\deadfish1_background.bmp");
			deadfish1->SetPos({ bgObjectPos.x + 929.0f, bgObjectPos.y + 378.0f });

			ImageObject* deadfish1Front = ya::object::Instantiate<ImageObject>(eColliderLayer::Background_front);
			deadfish1Front->SetImage(L"Mission1_part1_deadfish1_front", L"Background\\part1\\2.7\\deadfish1_front.bmp");
			deadfish1Front->SetPos({ bgObjectPos.x + 929.0f, bgObjectPos.y + 378.0f });

			ImageObject* deadfish2 = ya::object::Instantiate<ImageObject>(eColliderLayer::Background);
			deadfish2->SetImage(L"Mission1_part1_deadfish2", L"Background\\part1\\2.7\\deadfish2_background.bmp");
			deadfish2->SetPos({ bgObjectPos.x + 1488.0f, bgObjectPos.y + 408.0f });

			ImageObject* chewmeinHouseBackground = ya::object::Instantiate<ImageObject>(eColliderLayer::Background);
			chewmeinHouseBackground->SetImage(L"Mission1_part1_chewmein_house_background", L"Background\\part1\\2.7\\chewmein_house_background.bmp");
			chewmeinHouseBackground->SetPos({ bgObjectPos.x + 2187.0f, bgObjectPos.y + 38.0f });

			ImageObject* chewmeinHouseFront = ya::object::Instantiate<ImageObject>(eColliderLayer::Background_front);
			chewmeinHouseFront->SetImage(L"Mission1_part1_chewmein_house_background_front", L"Background\\part1\\2.7\\chewmein_house_front.bmp");
			chewmeinHouseFront->SetPos({ bgObjectPos.x + 2187.0f, bgObjectPos.y + 38.0f });

			CollisionObject* chewmeinHouseCollision = ya::object::Instantiate<CollisionObject>(eColliderLayer::MapObject);
			chewmeinHouseCollision->SetSize({ 170.0f, 260.0f });
			chewmeinHouseCollision->SetPos({ bgObjectPos.x + 2245.0f + 85.0f, bgObjectPos.y + 95.0f + 130.0f });

			Part1ChewmeinHouse* chewmeinHouseEvent = ya::object::Instantiate<Part1ChewmeinHouse>(eColliderLayer::Event);
		}

		Chewmein* chewmein1 = ya::object::Instantiate<Chewmein>(eColliderLayer::Monster);
		chewmein1->SetPos({ 1200.0f, 200.0f });
		backgroundPixel->AddObject(chewmein1);

		HeavyMachinegun* hm = ya::object::Instantiate<HeavyMachinegun>(eColliderLayer::Item);
		hm->SetPos({ 400.0f, 400.0f });

		CameraWall* cameraWall = ya::object::Instantiate<CameraWall>(eColliderLayer::Event);

		Scene::Initialize();
	}

	void Mission1Scene::Tick()
	{
		Scene::Tick();
	}

	void Mission1Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void Mission1Scene::Enter()
	{
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projecttile, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Collider, true);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster_Projecttile, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Event, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Item, true);

		CollisionManager::SetLayer(eColliderLayer::Player_Projecttile, eColliderLayer::Monster_Projecttile, true);

		CollisionManager::SetLayer(eColliderLayer::MapObject, eColliderLayer::Player_Projecttile, true);
		CollisionManager::SetLayer(eColliderLayer::MapObject, eColliderLayer::Collider, true);
		CollisionManager::SetLayer(eColliderLayer::MapObject, eColliderLayer::Monster, true);
	}

	void Mission1Scene::Exit()
	{
		Camera::SetTarget(nullptr);
	}
}