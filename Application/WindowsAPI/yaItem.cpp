#include "yaItem.h"

#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaPixelImageObject.h"

#include "yaCollider.h"
#include "yaRigidbody.h"

#include "yaItemEffect.h"

namespace ya
{
	Item::Item()
		: GameObject()
		, mImage(nullptr)
		, mAnimator(nullptr)
	{
		mCollider = AddComponent<Collider>();
		mRigidbody = AddComponent<Rigidbody>();

		Scene* playScene = SceneManager::GetPlayScene();
		PixelImageObject* pixelImage = playScene->GetPixelImage();
		if (pixelImage != nullptr)
			pixelImage->AddObject(this);
	}

	Item::~Item()
	{
	}

	void Item::Initialize()
	{
	}

	void Item::Tick()
	{
		GameObject::Tick();
	}

	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Item::OnCollisionEnter(Collider* other)
	{
		ItemEffect* effect = new ItemEffect();
		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(effect, eColliderLayer::Effect);
		effect->SetPos(GetPos());
		effect->play();

		this->Death();
	}

	void Item::OnCollisionStay(Collider* other)
	{
	}

	void Item::OnCollisionExit(Collider* other)
	{
	}
}