#include "yaGrenade.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaAnimator.h"

#include "yaCamera.h"
#include "yaTime.h"

#include "yaCollider.h"
#include "yaRigidbody.h"

#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaGrenadeEffect.h"
#include "yaPixelImageObject.h"

namespace ya
{
	Grenade::Grenade()
		: mSpeed(800.0f)
		, mAliveTime(5.0f)
		, mDirection(Vector2::One)
		, mImage(nullptr)
		, mBounceCount(2)
	{
		SetScale({ M_SCALE, M_SCALE });
		SetSize({ 18.0f, 18.0f });

		{ // 애니메이션
			if (mImage == nullptr)
				mImage = Resources::Load<Image>(L"Grenade", L"..\\Resources\\Image\\Projecttile\\grenade.bmp");

			mAnimator = new Animator();
			mAnimator->CreateAnimation(L"grenade", mImage, Vector2(0.0f, 0.0f), Vector2(21.0f, 19.0f), Vector2(0.0f, 0.0f), 16, 0.07f);
			mAnimator->Play(L"grenade", true);

			AddComponent(mAnimator);
		}

		Collider* collider = AddComponent<Collider>();
		Rigidbody* rigidbody = AddComponent<Rigidbody>();

		Scene* playScene = SceneManager::GetPlayScene();
		PixelImageObject* pixelImage = playScene->GetPixelImage();
		if(pixelImage != nullptr)
			pixelImage->AddObject(this);
	}

	Grenade::~Grenade()
	{
	}

	void Grenade::Initialize()
	{
	}

	void Grenade::Tick()
	{
		GameObject::Tick();

		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		if (rigidbody != nullptr && rigidbody->isGround())
		{
			GrenadeEffect* effect = new GrenadeEffect();
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(effect, eColliderLayer::Effect);
			effect->SetPos(GetPos());
			effect->play();
			Death();

			return;
		}

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos.x += mSpeed * mDirection.x * Time::DeltaTime();
		pos.y += mSpeed * mDirection.y * Time::DeltaTime();

		SetPos(pos);
	}

	void Grenade::Render(HDC hdc)
	{
		/*Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 size = GetSize();
		pos = Camera::CalculatePos(pos);

		Vector2 rect;
		rect.x = mImage->GetWidth();
		rect.y = mImage->GetHeight();

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, pos.x - (size.x * scale.x / 2), pos.y - (size.y * scale.y / 2), rect.x * scale.x, rect.y * scale.y,
			mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);*/

		GameObject::Render(hdc);
	}

	void Grenade::OnCollisionEnter(Collider* other)
	{
		GameObject* gameObj = other->GetOwner();

		GrenadeEffect* effect = new GrenadeEffect();
		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(effect, eColliderLayer::Effect);
		effect->SetPos(GetPos());
		effect->play();

		this->Death();
	}

	void Grenade::OnCollisionStay(Collider* other)
	{
	}

	void Grenade::OnCollisionExit(Collider* other)
	{
	}
}