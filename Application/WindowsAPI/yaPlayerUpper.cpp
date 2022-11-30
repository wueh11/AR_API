#include "yaPlayerUpper.h"

#include "yaResources.h"
#include "yaInput.h"
#include "yaImage.h"

#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

namespace ya
{
	PlayerUpper::PlayerUpper()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
		SetName(L"PlayerUpper");
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
		SetSize({ 20.0f, 20.0f });
		SetOffset({ 2.0f, -16.0f });
	}

	PlayerUpper::~PlayerUpper()
	{
	}

	void PlayerUpper::Initialize()
	{
		GameObject* player = GetOwner();
		SetScale(player->GetScale());

		//Upper
		if (mImage == nullptr)
			mImage = Resources::Load<Image>(L"PlayerUpper", L"..\\Resources\\Image\\Player\\player_upper_pistol.bmp");

		mAnimator = new Animator();
		CreateAnimation();
		mAnimator->Play(L"IdlePistolRight", true);
		AddComponent(mAnimator);

		Collider* collider = new Collider();
		collider->SetSize(GetSize());
		collider->SetScale(GetScale());
		collider->SetOffset({ 0.0f, 0.0f });
		AddComponent(collider);
	}

	void PlayerUpper::Tick()
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
			//mAnimator->Play(L"WalkPistolRight", true, true);
		}
		else if (KEY_DOWN(eKeyCode::D))
		{
			mAnimator->Play(L"WalkPistolRight", true);
		}

		/*if (KEY_DOWN(eKeyCode::SPACE))
		{
			mAnimator->Play(L"JumpPistolRight", false);
		}
		if (KEY_UP(eKeyCode::W))
		{
			mAnimator->Play(L"IdlePistolRight", true);
		}
		if (KEY_UP(eKeyCode::S))
		{
			mAnimator->Play(L"IdlePistolRight", true);
		}
		if (KEY_UP(eKeyCode::A))
		{
			mAnimator->Play(L"IdlePistolRight", true);
		}
		if (KEY_UP(eKeyCode::D))
		{
			mAnimator->Play(L"IdlePistolRight", true);
		}*/

		SetPos(pos);
	}

	void PlayerUpper::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerUpper::OnCollisionEnter(Collider* other)
	{
	}

	void PlayerUpper::OnCollisionStay(Collider* other)
	{
	}

	void PlayerUpper::OnCollisionExit(Collider* other)
	{
	}

	void PlayerUpper::CreateAnimation()
	{
		//Pistol
		{
			//Right
			{
				mAnimator->CreateAnimation(L"Idle-Right-Pistol", mImage, Vector2(0.0f, 0.0f), Vector2(31.0f, 29.0f), Vector2(10.0f, 0.0f), 4, 0.2f);
				mAnimator->CreateAnimation(L"Walk-Right-Pistol", mImage, Vector2(0.0f, 62.0f), Vector2(34.0f, 29.0f), Vector2(8.0f, 0.0f), 12, 0.1f);
				mAnimator->CreateAnimation(L"Jump-Right-Pistol", mImage, Vector2(0.0f, 60.0f), Vector2(64.0f, 28.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
				mAnimator->CreateAnimation(L"JumpMove-Right-Pistol", mImage, Vector2(0.0f, 182.0f), Vector2(34.0f, 35.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
				mAnimator->CreateAnimation(L"Shoot-Right-Pistol", mImage, Vector2(0.0f, 256.0f), Vector2(52.0f, 30.0f), Vector2(2.0f, 0.0f), 10, 0.1f);
				mAnimator->CreateAnimation(L"Knife1-Right-Pistol", mImage, Vector2(0.0f, 318.0f), Vector2(43.0f, 48.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
				mAnimator->CreateAnimation(L"Knife2-Right-Pistol", mImage, Vector2(0.0f, 256.0f), Vector2(50.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
			}

			//Left
			{
				mAnimator->CreateAnimation(L"Idle-Left-Pistol", mImage, Vector2(0.0f, 30.0f), Vector2(31.0f, 29.0f), Vector2(10.0f, 0.0f), 4, 0.2f);
				mAnimator->CreateAnimation(L"Walk-Left-Pistol", mImage, Vector2(0.0f, 93.0f), Vector2(34.0f, 29.0f), Vector2(8.0f, 0.0f), 12, 0.1f);
				mAnimator->CreateAnimation(L"Jump-Left-Pistol", mImage, Vector2(0.0f, 152.0f), Vector2(64.0f, 28.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
				mAnimator->CreateAnimation(L"JumpMove-Left-Pistol", mImage, Vector2(0.0f, 219.0f), Vector2(34.0f, 35.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
				mAnimator->CreateAnimation(L"Shoot-Left-Pistol", mImage, Vector2(0.0f, 286.0f), Vector2(52.0f, 30.0f), Vector2(2.0f, 0.0f), 10, 0.1f);
				mAnimator->CreateAnimation(L"Knife1-Left-Pistol", mImage, Vector2(0.0f, 368.0f), Vector2(43.0f, 48.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
				mAnimator->CreateAnimation(L"Knife2-Left-Pistol", mImage, Vector2(0.0f, 453.0f), Vector2(50.0f, 30.0f), Vector2(2.0f, 0.0f), 6, 0.1f);
			}
		}

		//Heavy Machinegun
		{

		}

		//Flamegun
		{

		}
	}
}