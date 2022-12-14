#pragma once
#include "Common.h"

namespace ya
{
	class Image;
	class GameObject;
	class Camera
	{
	public:
		enum class eState
		{
			DEFAULT,
			TARGET,
			FIX,
			FREE,
			AUTO,
		};

	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }
		static void SetTarget(GameObject* gameObj) { mTarget = gameObj; }
		static void SetCameraEffect(eCameraEffect effect) { mEffect = effect; }
		static Vector2 GetLookPosition() { return mLookPosition; }

	public:
		static void SetState(eState state) { mState = state; }
		static void SetLookPosition(Vector2 lookPosition) { mLookPosition = lookPosition; }

		static void Reset();

	private:
		static void Default();
		static void Target();
		static void Fix();
		static void Free();
		static void Auto();

	private:
		Camera() = default;
		~Camera() = default;

	private:
		static Vector2 mResolution; // ȭ�� �ػ�
		static Vector2 mLookPosition; /// ī�޶� �ٶ󺸴� ��ǥ
		static Vector2 mDistance; // �ػ� �߽� ��ǥ�� ���� ī�޶��� ������ ///(ȭ���� �߰���ŭ ����)

		static GameObject* mTarget; /// ī�޶� ���󰡴� ���

		static eCameraEffect mEffect;
		static Image* mCutton; // ������ �̹���
		static float mAlphaTime;
		static float mCuttonAlpha;
		static float mEndTime;

		static float mSpeed;
		static float mMaxSpeed;

		static eState mState;
	};

}