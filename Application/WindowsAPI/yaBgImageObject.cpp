#include "yaBgImageObject.h"

#include "yaApplication.h"

#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaCamera.h"

namespace ya
{
	BgImageObject::BgImageObject()
		: mImage(nullptr)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
		SetSize(Vector2::Zero);
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

		//Vector2 pos = GetPos();
		//Vector2 lookPosition = Camera::GetLookPosition();

		//float speed = -96.0f;

		//if(lookPosition.x > Application::GetInstance().GetWindowData().width / 2)
		//{
		//	/*if (KEY_PRESS(eKeyCode::LEFT))
		//		pos.x -= speed * Time::DeltaTime();
		//	else if (KEY_PRESS(eKeyCode::RIGHT))
		//		pos.x += speed * Time::DeltaTime();*/

		//	if (KEY_PRESS(eKeyCode::RIGHT))
		//		pos.x += speed * Time::DeltaTime();
		//}

		//SetPos(pos);

		/*Vector2 pos = GetPos();
		pos = Camera::CalculatePos(pos);
		SetPos(pos);*/
	}

	void BgImageObject::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 size = GetSize();
		Vector2 scale = GetScale();

		Vector2 rect;
		rect.x = Application::GetInstance().GetWindowData().width;
		rect.y = Application::GetInstance().GetWindowData().height;

		TransparentBlt(hdc, pos.x, pos.y
			, size.x * scale.x, size.y * scale.y, mImage->GetDC()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void BgImageObject::SetImage(const std::wstring& key, const std::wstring& name)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += name;
		mImage = Resources::Load<Image>(key, path);
		SetSize({ (float)(mImage->GetWidth() * GetScale().x), (float)(mImage->GetHeight() * GetScale().y) });
	}
}