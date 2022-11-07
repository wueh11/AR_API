#pragma once
#include "yaComponent.h"

namespace ya
{
	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetScale(Vector2 scale) { mScale = scale; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetOffset(Vector2 offset) { mOffset = offset; }

		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }
		Vector2 GetSize() { return mSize; }
		Vector2 GetOffset() { return mOffset; }

	private:
		Vector2 mOffset;
		Vector2 mPos;
		Vector2 mScale;
		Vector2 mSize;

		UINT mCollisionCount;
	};
}