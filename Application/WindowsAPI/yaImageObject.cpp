#include "yaImageObject.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaApplication.h"
#include "yaCamera.h"

namespace ya
{
	ImageObject::ImageObject()
		: mImage(nullptr)
		, mFullClienet(false)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
		SetSize(Vector2::Zero);
	}

	ImageObject::~ImageObject()
	{
	}

	void ImageObject::Initialize()
	{

	}

	void ImageObject::Tick()
	{
		GameObject::Tick();
	}

	void ImageObject::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 size = GetSize();

		pos = Camera::CalculatePos(pos);

		if (mFullClienet)
		{
			Vector2 rect;
			rect.x = Application::GetInstance().GetWindowData().width;
			rect.y = Application::GetInstance().GetWindowData().height;

			TransparentBlt(hdc, pos.x, pos.y
				, rect.x, rect.y, mImage->GetDC()  ///dc, ������ġ, �̹��� ũ��, ������dc
				, 0, 0, mImage->GetWidth(), mImage->GetHeight() /// �̹����� ����, ���κ� ��ǥ(�ڸ���)
				, RGB(255, 255, 255)); ///crTransparent�� ���ڸ� ���ܽ�Ű�� ����Ѵ�.(����ó��)
		}
		else
		{
			TransparentBlt(hdc, pos.x, pos.y
				, size.x * scale.x, size.y * scale.y, mImage->GetDC()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight()
				, RGB(255, 0, 255));
		}

		GameObject::Render(hdc);
	}

	void ImageObject::SetImage(const std::wstring& key, const std::wstring& name)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += name;
		mImage = Resources::Load<Image>(key, path);
		SetSize({ (float)(mImage->GetWidth() * GetScale().x), (float)(mImage->GetHeight() * GetScale().y) });
	}
}