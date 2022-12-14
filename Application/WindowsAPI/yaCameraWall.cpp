#include "yaCameraWall.h"
#include "yaCollider.h"
#include "yaCamera.h"

#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaPlayer.h"

namespace ya
{
	CameraWall::CameraWall()
	{
		SetName(L"CameraWall");
		SetPos({ 0.0f, 0.0f });
		SetSize({ 20.0f, 400.0f });
	}
	CameraWall::~CameraWall()
	{
	}
	void CameraWall::Initialize()
	{
		CollisionObject::Initialize();
	}
	void CameraWall::Tick()
	{
		CollisionObject::Tick();

		Vector2 pos = GetPos();
		pos.x = Camera::GetLookPosition().x - 400.0f;
		pos.y = Camera::GetLookPosition().y;
		SetPos(pos);
	}

	void CameraWall::Render(HDC hdc)
	{
		CollisionObject::Render(hdc);
	}

	void CameraWall::OnCollisionEnter(Collider* other)
	{
		CollisionObject::OnCollisionEnter(other);
	}

	void CameraWall::OnCollisionStay(Collider* other)
	{
	}
	void CameraWall::OnCollisionExit(Collider* other)
	{
	}
}