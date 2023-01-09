#include "yaHugeHermitScene.h"

#include "yaApplication.h"
#include "yaInput.h"
#include "yaCamera.h"
#include "yaObject.h"

#include "yaCollisionManager.h"
#include "yaSceneManager.h"
#include "yaUIManager.h"

#include "yaPlayer.h"
#include "yaImageObject.h"
#include "yaBgImageObject.h"
#include "yaPixelImageObject.h"
#include "yaCollisionObject.h"

#include "yaMonster.h"

#include "yaHeavyMachinegun.h"

#include "yaUIInventory.h"

namespace ya
{
	HugeHermitScene::HugeHermitScene()
		: mPixelObject(nullptr)
	{
	}

	HugeHermitScene::~HugeHermitScene()
	{
	}

	void HugeHermitScene::Initialize()
	{
		Player* player = ya::object::Instantiate<Player>(eColliderLayer::Player);
		SetPlayer(player);
		Camera::SetTarget(player);

		WindowData windowData = Application::GetInstance().GetWindowData();

		BgImageObject* background = ya::object::Instantiate<BgImageObject>(eColliderLayer::Background);
		background->SetImage(L"Mission1_part1_background", L"Background\\part1\\2.7\\background.bmp");
		background->SetPos({ 0.0f, -176.0f });

		PixelImageObject* backgroundPixel = ya::object::Instantiate<PixelImageObject>(eColliderLayer::Background_pixel);
		backgroundPixel->SetImage(L"Mission1_part1_background_pixel", L"Background\\part1\\2.7\\background_pixel.bmp");
		backgroundPixel->SetPos({ 0.0f, -10.0f });
		backgroundPixel->AddObject(player);
		SetPixelImage(backgroundPixel);

		Vector2 bgObjectPos = backgroundPixel->GetPos();

		UIManager::Push(eUIType::INVENTORY);
		UIInventory* inven = UIManager::GetUIInstant<UIInventory>(eUIType::INVENTORY);
		inven->SetTarget(player);

		Scene::Initialize();
	}

	void HugeHermitScene::Tick()
	{
		Scene::Tick();
	}

	void HugeHermitScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void HugeHermitScene::Enter()
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

	void HugeHermitScene::Exit()
	{
		Camera::SetTarget(nullptr);
	}
}