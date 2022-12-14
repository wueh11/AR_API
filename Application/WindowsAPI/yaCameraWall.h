#pragma once
#include "yaGameObject.h"
#include "yaCollisionObject.h"

namespace ya
{
	class CameraWall : public CollisionObject
	{
	public:
		CameraWall();
		virtual ~CameraWall();

		virtual void Initialize() override;
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);
	};
}

