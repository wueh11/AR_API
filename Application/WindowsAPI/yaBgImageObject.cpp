#include "yaBgImageObject.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaApplication.h"

namespace ya
{
	BgImageObject::BgImageObject()
		: mImage(nullptr)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
	}

	BgImageObject::~BgImageObject()
	{
	}

	void BgImageObject::Initialize()
	{

	}

	void BgImageObject::Tick()
	{
		GameObject::Tick();
	}

	void BgImageObject::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 rect;
		rect.x = Application::GetInstance().GetWindowData().width;
		rect.y = Application::GetInstance().GetWindowData().height;

		TransparentBlt(hdc, pos.x, pos.y
			, rect.x, rect.y, mImage->GetDC()  ///dc, ������ġ, �̹��� ũ��, ������dc
			, 0, 0, mImage->GetWidth(), mImage->GetHeight() /// �̹����� ����, ���κ� ��ǥ(�ڸ���)
			, RGB(255, 255, 255)); ///crTransparent�� ���ڸ� ���ܽ�Ű�� ����Ѵ�.(����ó��)

		GameObject::Render(hdc);
	}

	void BgImageObject::SetImage(const std::wstring& key, const std::wstring& name)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += name;
		mImage = Resources::Load<Image>(key, path);
	}
}