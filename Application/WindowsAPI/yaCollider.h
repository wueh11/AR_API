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

		void SetScale(Vector2 scale) { mScale = scale; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetOffset(Vector2 offset) { mOffset = offset; }

	private:
		Vector2 mOffset;
		Vector2 mPos;
		Vector2 mScale;
	};
}