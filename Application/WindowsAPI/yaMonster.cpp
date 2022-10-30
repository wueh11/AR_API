#include "yaMonster.h"

#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaImage.h"
#include "yaResources.h"

#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	Monster::Monster()
		: mSpeed(1.0f)
	{
		SetPos({ 200.0f, 400.0f });
		SetScale({ 2.0f, 2.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster", L"..\\Resources\\Image\\Monster.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
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

		TransparentBlt(hdc, finalPos.x, finalPos.y
			, rect.x, rect.y, mImage->GetDC()  ///dc, ������ġ, �̹��� ũ��, ������dc
			, 0, 0, mImage->GetWidth(), mImage->GetHeight() /// �̹����� ����, ���κ� ��ǥ(�ڸ���)
			, RGB(255, 255, 255)); ///crTransparent�� ���ڸ� ���ܽ�Ű�� ����Ѵ�.(����ó��)

		GameObject::Render(hdc); /// �ڽ��� �����׷�������
	}
}