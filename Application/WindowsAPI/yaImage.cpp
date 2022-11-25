#include "yaImage.h"
#include "yaApplication.h"
#include "yaResources.h"

namespace ya
{
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Image::~Image()
	{
		HWND hWnd = Application::GetInstance().GetWindowData().hWnd;
		ReleaseDC(hWnd, mHdc);
	}

	Image* Image::Create(const std::wstring& key, UINT width, UINT height)
	{
		Image* image = Resources::Find<Image>(key);

		if (image != nullptr)
		{
			MessageBox(nullptr, L"중복키 이미지 생성", L"이미지 생성 실패!", MB_OK);
			return nullptr;
		}

		image = new Image();
		HDC mainHdc = Application::GetInstance().GetHdc();

		image->mBitmap = CreateCompatibleBitmap(mainHdc, width, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		if (image->mBitmap == NULL || image->mHdc == NULL)
			return nullptr;

		// 새로 생성한 비트맵과 DC를 서로 연결
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(defaultBitmap);

		BITMAP bitmap = {};
		GetObject(image->mBitmap, sizeof(BITMAP), &bitmap);

		image->mWidth = bitmap.bmWidth;
		image->mHeight = bitmap.bmHeight;
		image->SetKey(key);

		Resources::Insert<Image>(key, image);

		return image;
	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str()
			, IMAGE_BITMAP, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
		{
			return E_FAIL;
		}

		BITMAP bitInfo = {};

		GetObject(mBitmap, sizeof(BITMAP), &bitInfo); ///mBitmap으로 불러온 파일의 bitmap 정보를 bitInfo에 가져옴

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);	/// hdc 복사하여 Image hdc 생성 -> hdc를 각각 갖고 있으면 hdc마다 색깔,이미지를 지정할 수 있기 때문에

		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap); ///mHdc를 mBitmap으로 바꿈
		DeleteObject(prevBit);

		return S_OK;
	}

	Pixel Image::GetPixelImage(int x, int y)
	{
		COLORREF rgba = GetPixel(mHdc, x, y);
		return Pixel(rgba);
	}

	void Image::SetPixel(int x, int y, Pixel pixel)
	{
		// 비트맵 좌표는 좌측 하단이 0,0
		// 윈도우 좌표처럼 사용하려면 y를 반대로 바꾸어 주어야 한다.
		y = mHeight - (y + 1);

		Pixel* bitmapPixel = (Pixel*)mBitmap;
		bitmapPixel += (mWidth * y + x);

		*bitmapPixel = pixel;
	}
}