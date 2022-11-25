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
			MessageBox(nullptr, L"�ߺ�Ű �̹��� ����", L"�̹��� ���� ����!", MB_OK);
			return nullptr;
		}

		image = new Image();
		HDC mainHdc = Application::GetInstance().GetHdc();

		image->mBitmap = CreateCompatibleBitmap(mainHdc, width, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		if (image->mBitmap == NULL || image->mHdc == NULL)
			return nullptr;

		// ���� ������ ��Ʈ�ʰ� DC�� ���� ����
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

		GetObject(mBitmap, sizeof(BITMAP), &bitInfo); ///mBitmap���� �ҷ��� ������ bitmap ������ bitInfo�� ������

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);	/// hdc �����Ͽ� Image hdc ���� -> hdc�� ���� ���� ������ hdc���� ����,�̹����� ������ �� �ֱ� ������

		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap); ///mHdc�� mBitmap���� �ٲ�
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
		// ��Ʈ�� ��ǥ�� ���� �ϴ��� 0,0
		// ������ ��ǥó�� ����Ϸ��� y�� �ݴ�� �ٲپ� �־�� �Ѵ�.
		y = mHeight - (y + 1);

		Pixel* bitmapPixel = (Pixel*)mBitmap;
		bitmapPixel += (mWidth * y + x);

		*bitmapPixel = pixel;
	}
}