#pragma once
#include "yaGameObject.h"
#include "yaImage.h"

namespace ya
{
	class Image;
	class BgImageObject : public GameObject
	{
	public:
		BgImageObject();
		virtual ~BgImageObject();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& imageName);

	private:
		Image* mImage;
		const std::wstring mImageName;
	};
}