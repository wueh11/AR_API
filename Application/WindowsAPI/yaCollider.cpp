#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaApplication.h"
#include "yaCamera.h"

namespace ya
{
	Collider::Collider()
		:Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(Vector2(100.0f, 100.0f))
		, mScale(Vector2::One)
		, mCollisionCount(0)
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
	}

	void Collider::Render(HDC hdc)
	{
		///brush
		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);

		///pen
		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = NULL;

		if (mCollisionCount > 0) /// 충돌이 있으면 펜을 빨간색으로
			oldPen = (HPEN)SelectObject(hdc, redPen);
		else
			oldPen = (HPEN)SelectObject(hdc, greenPen);

		mPos = Camera::CalculatePos(mPos);

		GameObject* owner = GetOwner();
		mSize = owner->GetSize();

		Rectangle(hdc, mPos.x - (mSize.x / 2.0f), mPos.y - (mSize.y / 2.0f)
			, mPos.x + (mSize.x / 2.0f), mPos.y + (mSize.y / 2.0f));
		/*Rectangle(hdc, mPos.x - (mScale.x / 2.0f), mPos.y - (mScale.y / 2.0f)
			, mPos.x + (mScale.x / 2.0f), mPos.y + (mScale.y / 2.0f));*/

		SelectObject(hdc, oldPen);
		DeleteObject(redPen);
		DeleteObject(greenPen);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mCollisionCount++;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		mCollisionCount--;
		GetOwner()->OnCollisionExit(other);
	}
}