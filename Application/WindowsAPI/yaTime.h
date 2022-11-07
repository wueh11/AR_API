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
		//CPU 고유 진동수 ( 1초당 몇번 ) -> 진동 횟수를 통해 몇초가 지났는지 계산
		static LARGE_INTEGER mCpuFrequency;	// cpu 고유 진동수
		static LARGE_INTEGER mPrevFrequency;	// 이전프레임 진동수
		static LARGE_INTEGER mCurFrequency;	// 현재프레임 진동수

		static float mDeltaTime;
		static float mTime;
	};
}
