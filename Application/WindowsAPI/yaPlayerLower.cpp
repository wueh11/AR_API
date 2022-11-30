#include "yaPlayerLower.h"

#include "yaResources.h"
#include "yaInput.h"
#include "yaImage.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

namespace ya
{
	PlayerLower::PlayerLower()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
		SetName(L"PlayerLower");
		SetPos({ 0.0f, 0.0f });
		SetScale(Vector2::One);
		SetSize({ 20.0f, 15.0f });
		SetOffset({ 2.0f, 30.0f });
	}

	PlayerLower::~PlayerLower()
	{
	}

	void PlayerLower::Initialize()
	{
		GameObject* player = GetOwner();
		SetScale(player->GetScale());

		if (mImage == nullptr)
			mImage = Resources::Load<Image>(L"PlayerLower", L"..\\Resources\\Image\\Player\\player_lower.bmp");

		mAnimator = new Animator();
		CreateAnimation();
		mAnimator->Play(L"IdleRight", true);
		AddComponent(mAnimator);

		Collider* collider = new Collider();
		collider->SetSize(GetSize());
		collider->SetScale(GetScale());
		collider->SetOffset({ 0.0f, 0.0f });
		AddComponent(collider);
	}

	void PlayerLower::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetOwner()->GetPos() + GetOffset();

		if (KEY_DOWN(eKeyCode::W))
		{
			//mAnimator->Play(L"MoveUp", true);
		}
		else if (KEY_DOWN(eKeyCode::S))
		{
			//mAnimator->Play(L"MoveDown", true);
		}
		else if (KEY_DOWN(eKeyCode::A))
		{
			mAnimator->Play(L"WalkLeft", true);
		}
		else if (KEY_DOWN(eKeyCode::D))
		{
			mAnimator->Play(L"WalkRight", true);
		}

		if (KEY_UP(eKeyCode::W))
		{
		}
		if (KEY_UP(eKeyCode::S))
		{
		}
		if (KEY_UP(eKeyCode::A))
		{
			mAnimator->Play(L"IdleLeft", true);
		}
		if (KEY_UP(eKeyCode::D))
		{
			mAnimator->Play(L"IdleRight", true);
		}

		SetPos(pos);
	}

	void PlayerLower::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerLower::OnCollisionEnter(Collider* other)
	{
	}

	void PlayerLower::OnCollisionStay(Collider* other)
	{
	}

	void PlayerLower::OnCollisionExit(Collider* other)
	{
	}

	void PlayerLower::CreateAnimation()
	{
		//Right
		{
			mAnimator->CreateAnimation(L"IdleRight", mImage, Vector2(0.0f, 0.0f), Vector2(21.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			mAnimator->CreateAnimation(L"WalkRight", mImage, Vector2(0.0f, 35.0f), Vector2(33.0f, 20.0f), Vector2(0.0f, 0.0f), 12, 0.1f);
			mAnimator->CreateAnimation(L"JumpRight", mImage, Vector2(0.0f, 78.0f), Vector2(21.0f, 24.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
			mAnimator->CreateAnimation(L"JumpMoveRight", mImage, Vector2(0.0f, 129.0f), Vector2(33.0f, 21.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
		}

		//Left
		{
			mAnimator->CreateAnimation(L"IdleLeft", mImage, Vector2(0.0f, 17.0f), Vector2(21.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			mAnimator->CreateAnimation(L"WalkLeft", mImage, Vector2(0.0f, 56.0f), Vector2(33.0f, 20.0f), Vector2(0.0f, 0.0f), 12, 0.1f);
			mAnimator->CreateAnimation(L"JumpLeft", mImage, Vector2(0.0f, 103.0f), Vector2(21.0f, 24.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
			mAnimator->CreateAnimation(L"JumpMoveLeft", mImage, Vector2(0.0f, 151.0f), Vector2(33.0f, 21.0f), Vector2(0.0f, 0.0f), 6, 0.1f);
		}
	
	}
}