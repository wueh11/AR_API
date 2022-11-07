#pragma once
#include "Common.h"

namespace ya
{
	class Time
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static float DeltaTime() { return mDeltaTime; }

	private:
		//CPU ���� ������ ( 1�ʴ� ��� ) -> ���� Ƚ���� ���� ���ʰ� �������� ���
		static LARGE_INTEGER mCpuFrequency;	// cpu ���� ������
		static LARGE_INTEGER mPrevFrequency;	// ���������� ������
		static LARGE_INTEGER mCurFrequency;	// ���������� ������

		static float mDeltaTime;
		static float mTime;
	};
}
