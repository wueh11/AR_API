#include "yaTime.h"
#include "yaApplication.h"

namespace ya
{
	LARGE_INTEGER Time::mCpuFrequency; // static 초기화
	LARGE_INTEGER Time::mPrevFrequency;
	LARGE_INTEGER Time::mCurFrequency;
	float Time::mDeltaTime = 0.0f;
	float Time::mTime = 0.0f;

	void Time::Initialize()
	{
		// CPU 초당 반복되는 진동수를 얻어오는 함수
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램 싲가 했을때 cpu의 클럭 수
		QueryPerformanceCounter(&mPrevFrequency); //최초 진동수 계싼
	}

	void Time::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differrenceFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart); //(현재진동수 - 이전진동수) -> 한프레임당 얼마나 진동했는지 

		mDeltaTime = differrenceFrequency / static_cast<float>(mCpuFrequency.QuadPart); //한 프레임동안 걸린 시간

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			wchar_t szFloat[50] = {};

			//디버깅모드에서 작업할때 30프레임 이하 -> 최적화 고려...
			float fps = 1.0f / mDeltaTime;
			swprintf_s(szFloat, 50, L"fps : %f", fps);

			HWND hWnd = Application::GetInstance().GetWindowData().hWnd;
			SetWindowText(hWnd, szFloat);

			mTime = 0.0f;
		}
	}
}