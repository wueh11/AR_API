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
		GameObject::Render(hdc); /// �ڽ��� �����׷�������
	}

	void Hostage::OnCollisionEnter(Collider* other)
	{
		// �Ѿ� �Ǵ� �÷��̾� �������ݰ� �浹�� ���ٿ� Ǯ���� �翷���� �Դٰ���
		 
		
		// �÷��̾�� �浹�� �Դٰ��� ���߰� �������� drop
	}

	void Hostage::OnCollisionStay(Collider* other)
	{
	}

	void Hostage::OnCollisionExit(Collider* other)
	{
	}
}