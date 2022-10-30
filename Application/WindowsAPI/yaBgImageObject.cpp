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
			, rect.x, rect.y, mImage->GetDC()  ///dc, 시작위치, 이미지 크기, 복사할dc
			, 0, 0, mImage->GetWidth(), mImage->GetHeight() /// 이미지의 시작, 끝부분 좌표(자르기)
			, RGB(255, 255, 255)); ///crTransparent의 인자를 제외시키고 출력한다.(투명처리)

		GameObject::Render(hdc);
	}

	void BgImageObject::SetImage(const std::wstring& key, const std::wstring& name)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += name;
		mImage = Resources::Load<Image>(key, path);
	}
}