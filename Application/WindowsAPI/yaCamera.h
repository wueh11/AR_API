#pragma once
#include "Common.h"

namespace ya
{
	class Image;
	class GameObject;
	class Camera
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }
		static void SetTarget(GameObject* gameObj) { mTarget = gameObj; }
		static void SetCameraEffect(eCameraEffect effect) { mEffect = effect; }

	private:
		Camera() = default;
		~Camera() = default;

	private:
		static Vector2 mResolution; // 화면 해상도
		static Vector2 mLookPosition; /// 카메라가 바라보는 좌표
		static Vector2 mDistance; // 해상도 중심 좌표와 현재 카메라의 간격차 ///(화면의 중간만큼 간격)

		static GameObject* mTarget; /// 카메라가 따라가는 대상

		static eCameraEffect mEffect;
		static Image* mCutton; // 검정색 이미지
		static float mAlphaTime;
		static float mCuttonAlpha;
		static float mEndTime;
	};

}