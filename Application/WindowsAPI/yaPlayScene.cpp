#include "yaPlayScene.h"
#include "yaInput.h"

#include "yaCollisionManager.h"
#include "yaSceneManager.h"

#include "yaBgImageObject.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaRock.h"

#include "yaObject.h"

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
		/*BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"PlayBG", L"PlayBG.bmp");
		bg->Initialize();*/
		//AddGameObject(bg, eColliderLayer::Background);

		/*ya::object::Instantiate<Player>(eColliderLayer::Player);
		mons[0] = ya::object::Instantiate<Monster>(eColliderLayer::Monster);
		mons[1] = ya::object::Instantiate<Monster>({ 300.0f, 100.0f }, eColliderLayer::Monster);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projecttile, true);
		CollisionManager::SetLayer(eColliderLayer::Monster_Projecttile, eColliderLayer::Player_Projecttile, true);*/
	}

	void PlayScene::Tick()
	{
		Scene::Tick();

		/*if (rand() % 2000 > 1990)
		{
			Rock* rock = new Rock();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(rock, eColliderLayer::Monster_Projecttile);
		}*/
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