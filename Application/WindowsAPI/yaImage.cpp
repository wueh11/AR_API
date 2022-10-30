#include "yaImage.h"
#include "yaApplication.h"

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
}