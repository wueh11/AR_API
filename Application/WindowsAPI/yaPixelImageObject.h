#pragma once
#include "yaGameObject.h"
#include "yaImage.h"

namespace ya
{
	class Image;
	class Player;
	class PixelImageObject : public GameObject
	{
	public:
		PixelImageObject();
		virtual ~PixelImageObject();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& imageName);
		void SetFullClient(bool fullClient) { mFullClienet = fullClient; }

	private:
		Image* mImage;
		const std::wstring mImageName;

		bool mFullClienet;

		Player* mPlayer;
	};
}
