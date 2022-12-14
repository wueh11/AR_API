#include "yaPixelImageObject.h"

#include "yaApplication.h"
#include "yaResources.h"
#include "yaImage.h"

#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaCamera.h"
#include "yaPlayer.h"
#include "yaGameObject.h"
#include "yaRigidbody.h"

namespace ya
{
	PixelImageObject::PixelImageObject()
		: mImage(nullptr)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);

		Scene* playScene = SceneManager::GetPlayScene();
		mPlayer = playScene->GetPlayer();
	}

	PixelImageObject::~PixelImageObject()
	{
	}

	void PixelImageObject::Initialize()
	{
	}

	void PixelImageObject::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();

		for (GameObject* object : mObjects)
		{
			if (object == nullptr || object->GetComponent<Rigidbody>() == nullptr)
				return;

			Vector2 objectPos = object->GetPos();
			Vector2 objectSize = object->GetSize();
			Vector2 objectScale = object->GetScale();

			Pixel pixel = mImage->GetPixelImage(objectPos.x - pos.x, objectPos.y - pos.y + (objectSize.y * objectScale.y / 2));

			if (pixel.R == 0 && pixel.G == 255 && pixel.B == 0)
			{
				Pixel pixel2 = mImage->GetPixelImage(objectPos.x - pos.x, objectPos.y - pos.y + (objectSize.y * objectScale.y / 2) - 1.0f);
				if (pixel2.R == 0 && pixel2.G == 255 && pixel2.B == 0)
				{
					object->GetComponent<Rigidbody>()->SetGround(true);
					objectPos.y -= 1.0f;
					object->SetPos(objectPos);
				}
			}
			else
			{
				if(object->GetComponent<Rigidbody>()->IsPixel())
					object->GetComponent<Rigidbody>()->SetGround(false);
			}
		}


		/*Vector2 pos = GetPos();

		Vector2 playerPos = mPlayer->GetPos();
		Vector2 playerSize = mPlayer->GetSize();
		Vector2 playerScale = mPlayer->GetScale();

		Pixel pixel = mImage->GetPixelImage(playerPos.x - pos.x , playerPos.y - pos.y + (playerSize.y * playerScale.x / 2 ));

		if (pixel.R == 0 && pixel.G == 255 && pixel.B == 0)
		{
			Pixel pixel2 = mImage->GetPixelImage(playerPos.x - pos.x, playerPos.y - pos.y + (playerSize.y * playerScale.y / 2 ) - 1.0f);
			if (pixel2.R == 0 && pixel2.G == 255 && pixel2.B == 0)
			{
				mPlayer->GetComponent<Rigidbody>()->SetGround(true); 
				playerPos.y -= 1.0f;
				mPlayer->SetPos(playerPos);
			}
		}
		else
		{
			mPlayer->GetComponent<Rigidbody>()->SetGround(false);
		}*/
	}

	void PixelImageObject::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 size = GetSize();

		pos = Camera::CalculatePos(pos);

		TransparentBlt(hdc, pos.x, pos.y
			, size.x * scale.x, size.y * scale.y, mImage->GetDC()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void PixelImageObject::SetImage(const std::wstring& key, const std::wstring& name)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += name;
		mImage = Resources::Load<Image>(key, path);
		SetSize({ (float)(mImage->GetWidth() * GetScale().x), (float)(mImage->GetHeight() * GetScale().y) });
	}
}