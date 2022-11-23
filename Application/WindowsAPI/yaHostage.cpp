#include "yaHostage.h"

#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaImage.h"
#include "yaResources.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"

namespace ya
{
	Hostage::Hostage()
		: mSpeed(1.0f)
	{
		SetPos({ 450.0f, 100.0f });
		SetScale({ 3.0f, 3.0f });

		Initialize();
	}

	Hostage::~Hostage()
	{
	}

	void Hostage::Initialize()
	{
		SetName(L"Hostage");
		SetSize({ (float)(mImage->GetWidth() * GetScale().x), (float)(mImage->GetHeight() * GetScale().y) });

		AddComponent(new Animator());
		AddComponent(new Collider());
	}

	void Hostage::Tick()
	{
		GameObject::Tick();
	}

	void Hostage::Render(HDC hdc)
	{
		GameObject::Render(hdc); /// 자식이 먼저그려져양함
	}

	void Hostage::OnCollisionEnter(Collider* other)
	{
		// 총알 또는 플레이어 근접공격과 충돌시 밧줄에 풀려나 양옆으로 왔다갔다
		 
		
		// 플레이어와 충돌시 왔다갔다 멈추고 아이템을 drop
	}

	void Hostage::OnCollisionStay(Collider* other)
	{
	}

	void Hostage::OnCollisionExit(Collider* other)
	{
	}
}