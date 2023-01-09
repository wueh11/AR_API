#include <Windows.h>
#include "framework.h"
#include "WindowsAPI.h"

#include "yaApplication.h"

#include "yaResources.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaCamera.h"

#include "yaCollisionManager.h"
#include "yaSceneManager.h"
#include "yaUIManager.h"

namespace ya
{
	void Application::Inititalize(WindowData& data)
	{
		srand(time(NULL));
		initializeWindow(data);

		Time::Initialize();
		Input::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();
	}

	void Application::Tick()
	{
		Time::Tick();
		Input::Tick();

		SceneManager::Tick();
		CollisionManager::Tick();
		UIManager::Tick();
		Camera::Tick();

		Brush brush(mWindowData.backBuffer, mBrushs[(UINT)eBrushColor::Gray]);
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);
		
		SceneManager::Render(mWindowData.backBuffer);
		UIManager::Render(mWindowData.backBuffer);
		Camera::Render(mWindowData.backBuffer);
		Input::Render(mWindowData.backBuffer);
		Time::Render(mWindowData.backBuffer);

		// BitBlt는 DC간의 이미지를 복사해주는 함수
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height, mWindowData.backBuffer, 0, 0, SRCCOPY); ///backbuffer에 있는 이미지를 hdc에 복사

		SceneManager::DestroyGameObject();
	}

	eSceneType Application::GetPlaySceneType()
	{
		return SceneManager::GetPlaySceneType();
	}

	Application::Application()
	{
		mWindowData.clear(); //초기화
	}

	Application::~Application()
	{
		SceneManager::Release();
		Resources::Release();
		UIManager::Release();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hWnd, mWindowData.backBuffer);
	}

	void Application::initializeWindow(WindowData& data)
	{
		mWindowData = data;
		mWindowData.hdc = GetDC(data.hWnd);

		// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
		RECT rect = { 0, 0, mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경
		SetWindowPos(mWindowData.hWnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, SWP_NOMOVE | SWP_NOZORDER
		);

		ShowWindow(mWindowData.hWnd, true);

		///더블버퍼링 구현
		mWindowData.backtexture = CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);
		mWindowData.backBuffer = CreateCompatibleDC(mWindowData.hdc);

		HBITMAP defaultmap = (HBITMAP)SelectObject(mWindowData.backBuffer, mWindowData.backtexture); ///기존 버퍼 저장

		DeleteObject(defaultmap);

		// 메모리 해제해주어야한다.
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		mBrushs[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushs[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushs[(UINT)eBrushColor::Gray] = CreateSolidBrush(RGB(71, 71, 71));
		mBrushs[(UINT)eBrushColor::White] = (HBRUSH)GetStockObject(WHITE_BRUSH);

	}
}