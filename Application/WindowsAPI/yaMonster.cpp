#include "yaMonster.h"

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
	Monster::Monster()
		: mSpeed(1.0f)
	{
		SetPos({ 450.0f, 100.0f });
		SetScale({ 3.0f, 3.0f });

		Initialize();
	}

	Monster::Monster(Vector2 position)
		: mSpeed(1.0f)
	{
		SetPos(position);
		SetScale({ 3.0f, 3.0f });

		Initialize();
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		SetName(L"Monster");
		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster", L"..\\Resources\\Image\\Monster.bmp");
		}
		SetSize({ (float)(mImage->GetWidth() * GetScale().x), (float)(mImage->GetHeight() * GetScale().y) });

		//AddComponent(new Animator());
		AddComponent(new Collider());
	}

	void Monster::Tick()
	{
		GameObject::Tick();
	}

	void Monster::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = pos.x - mImage->GetWidth() * (scale.x / 2.0f);
		finalPos.y = pos.y - mImage->GetHeight() * (scale.y / 2.0f);

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		finalPos = Camera::CalculatePos(finalPos);

		TransparentBlt(hdc, finalPos.x, finalPos.y
			, rect.x, rect.y, mImage->GetDC()  ///dc, ������ġ, �̹��� ũ��, ������dc
			, 0, 0, mImage->GetWidth(), mImage->GetHeight() /// �̹����� ����, ���κ� ��ǥ(�ڸ���)
			, RGB(255, 0, 255)); ///crTransparent�� ���ڸ� ���ܽ�Ű�� ����Ѵ�.(����ó��)

		GameObject::Render(hdc); /// �ڽ��� �����׷�������
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
	}

	void Monster::OnCollisionStay(Collider* other)
	{
	}

	void Monster::OnCollisionExit(Collider* other)
	{
	}
}