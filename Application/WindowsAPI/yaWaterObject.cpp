#include "yaWaterObject.h"

#include "yaCamera.h"
#include "yaCollider.h"

#include "yaWaterEffect.h"

#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	WaterObject::WaterObject()
		: mCollider(nullptr)
		, mWaterEffect(nullptr)
	{
		SetPos({ 425.0f, 530.0f });
		SetSize({ 850.0f, 90.0f });
	}
	WaterObject::~WaterObject()
	{
	}

	void WaterObject::Initialize()
	{
		mCollider = new Collider();
		AddComponent(mCollider);

		mWaterEffect = new WaterEffect();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(mWaterEffect, eColliderLayer::Effect);
	}

	void WaterObject::Tick()
	{
		GameObject::Tick();
	}

	void WaterObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void WaterObject::OnCollisionEnter(Collider* other)
	{
		GameObject* target = other->GetOwner();

		if (target == nullptr)
			return;

		Vector2 pos = GetPos();
		Vector2 size = GetSize();

		Vector2 targetPos = target->GetPos();

		if (targetPos.x < pos.x + size.x / 2)
			mWaterEffect->SetState(ya::WaterEffect::eState::FALL);
		else
		{
			mWaterEffect->SetState(ya::WaterEffect::eState::WALK);
			mWaterEffect->Show();
		}

		mWaterEffect->SetPos({ targetPos.x, targetPos.y + 25.0f });
	}

	void WaterObject::OnCollisionStay(Collider* other)
	{
		GameObject* target = other->GetOwner();

		if (target == nullptr)
			return;

		Vector2 targetPos = target->GetPos();
		mWaterEffect->SetPos({targetPos.x, targetPos.y + 25.0f});
	}

	void WaterObject::OnCollisionExit(Collider* other)
	{
		GameObject* target = other->GetOwner();

		if (target == nullptr)
			return;

		Vector2 pos = GetPos();
		Vector2 size = GetSize();

		Vector2 targetPos = target->GetPos();

		if (targetPos.x < pos.x + size.x / 2)
			mWaterEffect->SetState(ya::WaterEffect::eState::JUMP);
		else
		{
			mWaterEffect->SetState(ya::WaterEffect::eState::WALK);
			mWaterEffect->Hide();
		}

		mWaterEffect->SetPos({ targetPos.x, targetPos.y + 25.0f });
	}
}
