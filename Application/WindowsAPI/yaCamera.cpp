#include "yaCamera.h"
#include "yaApplication.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaImage.h"

namespace ya
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	eCameraEffect Camera::mEffect = eCameraEffect::None;
	Image* Camera::mCutton = nullptr; // 검정색 이미지
	float Camera::mAlphaTime = 0.0f;
	float Camera::mCuttonAlpha = 0.0f;
	float Camera::mEndTime = 1.0f;

	void Camera::Initialize()
	{
		WindowData data = Application::GetInstance().GetWindowData();
		mResolution = Vector2(data.width, data.height);
		mLookPosition = (mResolution / 2.0f);

		mEffect = eCameraEffect::FadeIn;
		mCutton = Image::Create(L"CameraCutton", 1600, 900);
	}

	void Camera::Tick()
	{
		if (mAlphaTime <= mEndTime)
		{
			mAlphaTime += Time::DeltaTime();
			float ratio = (mAlphaTime / mEndTime);

			if (eCameraEffect::FadeIn == mEffect)
			{
				mCuttonAlpha = 1.0f - ratio;
			}
			else if (eCameraEffect::FadeOut == mEffect)
			{
				mCuttonAlpha = ratio;
			}
		}

		if (KEY_PRESS(eKeyCode::UP))
		{
			mLookPosition.y -= 200.0f * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::DOWN))
		{
			mLookPosition.y += 200.0f * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::LEFT))
		{
			mLookPosition.x -= 200.0f * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::RIGHT))
		{
			mLookPosition.x += 200.0f * Time::DeltaTime();
		}

		if (mTarget != nullptr)
			mLookPosition = mTarget->GetPos();

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		if (mCuttonAlpha <= 0.0f || mCuttonAlpha > 1.0f)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER; ///blend옵션 AC_SRC_OVER: 원본이미지와 다른이미지를 섞는다
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha); /// 투명도(alpha) 0~255

		AlphaBlend(hdc, 0, 0, mCutton->GetWidth(), mCutton->GetHeight(),
			mCutton->GetDC(), 0, 0, mCutton->GetWidth(), mCutton->GetHeight(), func);
	}
}