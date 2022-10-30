#include "yaTime.h"

namespace ya
{
	LARGE_INTEGER Time::mCpuFrequency; // static �ʱ�ȭ
	LARGE_INTEGER Time::mPrevFrequency;
	LARGE_INTEGER Time::mCurFrequency;
	float Time::mDeltaTime = 0.0f;

	void Time::Initialize()
	{
		// CPU �ʴ� �ݺ��Ǵ� �������� ������ �Լ�
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷� �밡 ������ cpu�� Ŭ�� ��
		QueryPerformanceCounter(&mPrevFrequency); //���� ������ ���
	}

	void Time::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differrenceFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart); //(���������� - ����������) -> �������Ӵ� �󸶳� �����ߴ��� 

		mDeltaTime = differrenceFrequency / static_cast<float>(mCpuFrequency.QuadPart); //�� �����ӵ��� �ɸ� �ð�

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		wchar_t szFloat[50] = {};

		//������忡�� �۾��Ҷ� 30������ ���� -> ����ȭ ���...
		float fps = 1.0f / mDeltaTime;

		swprintf_s(szFloat, 50, L"fps : %f", fps);
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 10, 10, szFloat, strLen);
	}
}