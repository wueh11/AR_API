#include "yaCharacterSelectScene.h"
#include "yaImageObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"

namespace ya
{
	CharacterSelectScene::CharacterSelectScene()
	{
	}

	CharacterSelectScene::~CharacterSelectScene()
	{
	}

	void CharacterSelectScene::Initialize()
	{
		ImageObject* bg = new ImageObject();
		bg->SetImage(L"CharacterSelectBackGround", L"selectScene.bmp");
		bg->Initialize();
		bg->SetPos({ 0.0f, 0.0f * M_SCALE });
		bg->SetScale({ M_SCALE, M_SCALE });
		AddGameObject(bg, eColliderLayer::Background);

		ImageObject* select = new ImageObject();
		select->SetImage(L"CharacterSelect", L"charactersSelect.bmp");
		select->Initialize();
		select->SetPos({ 0.0f, 0.0f * M_SCALE });
		select->SetScale({ M_SCALE, M_SCALE });
		AddGameObject(select, eColliderLayer::Background);
	}

	void CharacterSelectScene::Tick()
	{
		Scene::Tick();
	}

	void CharacterSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		Text text(hdc, L"Character Select", 10, 30);
	}

	void CharacterSelectScene::Enter()
	{
	}

	void CharacterSelectScene::Exit()
	{
	}
}