#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaApplication.h"
#include "yaCamera.h"
#include "yaCollisionManager.h"

namespace ya
{
	Collider::Collider()
		:Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(Vector2(100.0f, 100.0f))
		, mScale(Vector2::One)
		, mCollisionCount(0)
		, mbActive(true)
	{
		mScale = Vector2(100.0f, 100.0f);
	}

	Collider::~Collider()
	{
	}

	void Collider::Tick()
	{
		GameObject* owner = GetOwner();
		mPos = owner->GetPos() + mOffset;
		mSize = owner->GetSize();
		mScale = owner->GetScale();
	}

	void Collider::Render(HDC hdc)
	{
		if (CollisionManager::IsShow() == false)
			return;

		///brush
		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);

		///pen
		HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HPEN yellowPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		HPEN oldPen = NULL;

		if (mCollisionCount > 0) /// 충돌이 있으면 펜을 빨간색으로
			oldPen = (HPEN)SelectObject(hdc, redPen);
		else
			oldPen = (HPEN)SelectObject(hdc, greenPen);

		if(!mbActive)
			oldPen = (HPEN)SelectObject(hdc, yellowPen);

		mPos = Camera::CalculatePos(mPos);

		Rectangle(hdc, mPos.x - (mSize.x * mScale.x / 2.0f), mPos.y - (mSize.y * mScale.y / 2.0f)
			, mPos.x + (mSize.x * mScale.x / 2.0f), mPos.y + (mSize.y * mScale.y / 2.0f));

		SelectObject(hdc, oldPen);
		DeleteObject(redPen);
		DeleteObject(greenPen);
		DeleteObject(yellowPen);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		if (!mbActive)
			return;

		mCollisionCount++;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		if (!mbActive)
			return;

		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		if (!mbActive)
			return;

		mCollisionCount--;
		GetOwner()->OnCollisionExit(other);
	}
}