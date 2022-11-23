#include "yaMission1Scene.h"
#include "yaInput.h"

#include "yaCollisionManager.h"
#include "yaSceneManager.h"

#include "yaBgImageObject.h"
#include "yaImageObject.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaObject.h"
#include "yaChewmein.h"

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
		//¹è°æ
		ImageObject* bg = new ImageObject();
		bg->SetImage(L"Mission1_BG", L"background.bmp");
		bg->Initialize();
		bg->SetPos({ 0.0f, -64.0f * M_SCALE });
		bg->SetScale({ M_SCALE, M_SCALE });
		AddGameObject(bg, eColliderLayer::Background);

		ImageObject* bgObj = new ImageObject();
		bgObj->SetImage(L"Mission1_BG_obj_1", L"bgobj_0.bmp");
		bgObj->Initialize();
		bgObj->SetPos({ 0.0f, 00.0f });
		bgObj->SetScale({ M_SCALE, M_SCALE });
		AddGameObject(bgObj, eColliderLayer::Background);

		ya::object::Instantiate<Player>(eColliderLayer::Player);
		ya::object::Instantiate<Chewmein>(eColliderLayer::Monster);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
	}

	void Mission1Scene::Tick()
	{
		Scene::Tick();
	}

	void Mission1Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		Text text(hdc, L"Mission1", 10, 30);
	}

	void Mission1Scene::Enter()
	{
	}

	void Mission1Scene::Exit()
	{
	}
}