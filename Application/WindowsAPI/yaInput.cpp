#include "yaInput.h"

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
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
		{
			// �ش� Ű�� ���� ������ �ִ� ���
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				//���� �����ӿ� ������ �ִ� ���
				if (mKeys[i].bPressed)
					mKeys[i].state = eKeyState::PRESSED;
				//���� �����ӿ� ���������� �ʾ��� ���
				else
					mKeys[i].state = eKeyState::DOWN;

				mKeys[i].bPressed = true;
			}
			// ������ ���� ���� ���
			else
			{
				//���� �����ӿ� ������ �ִ� ���
				if (mKeys[i].bPressed)
					mKeys[i].state = eKeyState::UP;
				//���� �����ӿ� ���������� �ʾ��� ���
				else
					mKeys[i].state = eKeyState::NONE;

				mKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{

	}

	eKeyState Input::GetKeyState(eKeyCode keyCode)
	{
		return mKeys[(UINT)keyCode].state;
	}
}