#include "yaPart1ChewmeinHouse.h"
#include "yaCamera.h"
#include "yaCollider.h"

namespace ya
{
	Part1ChewmeinHouse::Part1ChewmeinHouse()
		: mCollider(nullptr)
	{
	}
	Part1ChewmeinHouse::~Part1ChewmeinHouse()
	{
	}
	void Part1ChewmeinHouse::Initialize()
	{
		SetPos({ 2020.0f, 300.0f });
		SetSize({ 20.0f, 200.0f});

		mCollider = new Collider();
		AddComponent(mCollider);
	}
	void Part1ChewmeinHouse::Tick()
	{
		GameObject::Tick();
	}
	void Part1ChewmeinHouse::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Part1ChewmeinHouse::OnCollisionEnter(Collider* other)
	{
		Vector2 pos = Camera::GetLookPosition();
		Camera::SetState(ya::Camera::eState::FIX);
		Camera::SetLookPosition({pos.x, pos.y});
	}
	void Part1ChewmeinHouse::OnCollisionStay(Collider* other)
	{
	}
	void Part1ChewmeinHouse::OnCollisionExit(Collider* other)
	{
	}
}
