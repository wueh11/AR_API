#include "yaInput.h"
#include "yaApplication.h"

namespace ya
{
	int ASCII[(UINT)eKeyCode::End]
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,

		VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3,
		VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6,
		VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
		VK_NUMPAD0,

		'1','2','3','4','5','6','7','8','9','0'
	};

	std::vector<Input::Key> Input::mKeys;
	Vector2 Input::mMousePos;

	void Input::Initialize()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
		{
			Key key;
			key.keyCode = (eKeyCode)i;
			key.state = eKeyState::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}

	void Input::Tick()
	{
		if (GetFocus())
		{
			for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
			{
				// 해당 키가 현재 눌러져 있는 경우
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					//이전 프레임에 눌러져 있던 경우
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::PRESSED;
					//이전 프레임에 눌러져있지 않았을 경우
					else
						mKeys[i].state = eKeyState::DOWN;

					mKeys[i].bPressed = true;
				}
				// 눌러져 있지 않은 경우
				else
				{
					//이전 프레임에 눌러져 있던 경우
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::UP;
					//이전 프레임에 눌러져있지 않았을 경우
					else
						mKeys[i].state = eKeyState::NONE;

					mKeys[i].bPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);
			HWND hwnd = Application::GetInstance().GetWindowData().hWnd;
			ScreenToClient(hwnd, &mousePos);
			mMousePos.x = mousePos.x;
			mMousePos.y = mousePos.y;
		}
		else /// focus 에서 벗어났을 때
		{
			for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
			{
				if (eKeyState::DOWN == mKeys[i].state || eKeyState::PRESSED == mKeys[i].state)
					mKeys[i].state = eKeyState::UP; /// 눌려있던 키를 UP으로 초기화
				else if (eKeyState::UP == mKeys[i].state)
					mKeys[i].state = eKeyState::NONE;

				mKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{
		/*wchar_t szFloat[50] = {};
		std::wstring str1 = L"Mouse : " + std::to_wstring(mMousePos.x) + L", " + std::to_wstring(mMousePos.y);
		swprintf_s(szFloat, 50, str1.c_str());
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 60, szFloat, strLen);*/
	}

	eKeyState Input::GetKeyState(eKeyCode keyCode)
	{
		return mKeys[(UINT)keyCode].state;
	}

	Vector2 Input::GetMousePos(HWND hWnd)
	{
		Vector2 vMousePos(-1.0f, -1.0f);

		if (GetFocus()) /// 윈도우 여러개일경우 예외처리 (현재 창에만 입력)
		{
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(hWnd, &mousePos);
			vMousePos.x = mousePos.x;
			vMousePos.y = mousePos.y;

			return vMousePos;
		}

		return vMousePos;
	}
}