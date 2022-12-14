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
	float Camera::mSpeed = 250.0f;

	ya::Camera::eState Camera::mState = ya::Camera::eState::DEFAULT;

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
		switch (mState)
		{
		case ya::Camera::eState::DEFAULT:
			Default();
			break;
		case ya::Camera::eState::TARGET:
			Target();
			break;
		case ya::Camera::eState::FIX:
			Fix();
			break;
		case ya::Camera::eState::FREE:
			Free();
			break;
		case ya::Camera::eState::AUTO:
			Auto();
			break;
		default:
			break;
		}

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
	}

	void Camera::Render(HDC hdc)
	{
		wchar_t szFloat[50] = {};
		std::wstring str = L"Camera[" + std::to_wstring((int)mState) + L"]: " + std::to_wstring(mLookPosition.x) + L", " + std::to_wstring(mLookPosition.y);
		swprintf_s(szFloat, 50, str.c_str());
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 300, 10, szFloat, strLen);

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

	void Camera::Reset()
	{
		mState == eState::DEFAULT;
	}

	void Camera::Default()
	{
		if (mTarget != nullptr)
			mState = eState::TARGET;

		if (KEY_DOWN(eKeyCode::NUM_9))
		{
			mState = eState::FREE;
			return;
		}
	}

	void Camera::Target()
	{
		if (KEY_DOWN(eKeyCode::NUM_9))
		{
			mState = eState::FREE;
			return;
		}

		if (mTarget == nullptr)
		{
			mState = eState::DEFAULT;
			return;
		}

		if (KEY_PRESS(eKeyCode::RIGHT))
		{
			if (mTarget->GetPos().x > mLookPosition.x - 100.0f)
				mLookPosition.x += mSpeed * Time::DeltaTime();
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Fix()
	{
		//카메라 특정 위치로 고정

		if (KEY_DOWN(eKeyCode::NUM_9))
		{
			mState = eState::FREE;
			return;
		}
	}

	void Camera::Free()
	{
		if (KEY_DOWN(eKeyCode::NUM_9))
		{
			mState = eState::DEFAULT;
			return;
		}

		float speed = 600.0f;

		if (KEY_PRESS(eKeyCode::NUM_8))
		{
			mLookPosition.y -= speed * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::NUM_2))
		{
			mLookPosition.y += speed * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::NUM_4))
		{
			mLookPosition.x -= speed * Time::DeltaTime();
		}
		if (KEY_PRESS(eKeyCode::NUM_6))
		{
			mLookPosition.x += speed * Time::DeltaTime();
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Auto()
	{
	}
}