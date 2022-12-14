#include "yaBullet.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaBulletEffect.h"

#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaPixelImageObject.h"
#include "yaRigidbody.h"

#include "yaMonster.h"

namespace ya
{
	Bullet::Bullet()
		: mSpeed(800.0f)
		, mAliveTime(1.0f)
		, mDirection(Vector2::One)
		, mImage(nullptr)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 1.0f, 1.0f });
		SetSize({ 24.0f, 24.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"playerBullet", L"..\\Resources\\Image\\Projecttile\\playerBullet.bmp");
		}

		Collider* collider = AddComponent<Collider>();

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		rigidbody->SetMass(0.0f);

		Scene* playScene = SceneManager::GetPlayScene();
		PixelImageObject* pixelImage = playScene->GetPixelImage();
		if (pixelImage != nullptr)
			pixelImage->AddObject(this);
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Initialize()
	{
	}

	void Bullet::Tick()
	{
		GameObject::Tick();

		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		if (rigidbody != nullptr && rigidbody->isGround())
		{
			BulletEffect* effect = new BulletEffect();
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(effect, eColliderLayer::Effect);
			effect->SetPos(GetPos());
			effect->play();
			Death();

			return;
		}

		mAliveTime -= Time::DeltaTime(); 
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		mDirection.Normalize();

		pos.x += mSpeed * mDirection.x * Time::DeltaTime();
		pos.y += mSpeed * mDirection.y * Time::DeltaTime();

		SetPos(pos);

		/*	if (abs(mDirection.x) > 0)
				scale.y = 0.5f;
			else
				scale.y = 1.0f;

			if (abs(mDirection.y) > 0)
				scale.x = 0.5f;
			else
				scale.x = 1.0f;

			SetScale(scale);*/
	}

	void Bullet::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
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
			mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

		GameObject::Render(hdc);
	}

	void Bullet::OnCollisionEnter(Collider* other)
	{
		Monster* monster = dynamic_cast<Monster*>(other->GetOwner());

		if(monster != nullptr)
		{
			monster->SetHp(-10);
		}

		BulletEffect* effect = new BulletEffect();
		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(effect, eColliderLayer::Effect);
		effect->SetPos(GetPos());
		effect->play();

		this->Death();
	}

	void Bullet::OnCollisionStay(Collider* other)
	{
	}

	void Bullet::OnCollisionExit(Collider* other)
	{
	}
}