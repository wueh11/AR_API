#pragma once

#define KEY_PRESS(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::PRESSED
#define KEY_DOWN(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::DOWN
#define KEY_UP(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::UP

enum class eSceneType
{
	Logo,
	Title,
	Play,
	End,
	MAX,
};

enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};

enum class eBrushColor
{
	Transparent,
	Black,
	Gray, //167 0 67
	White,
	Red,
	Green,
	Blue,
	End,
};

enum class eComponentType ///������Ʈ ������
{
	Animator,
	Collider,
	Sound,
	End,
};

#define _COLLIDER_LAYER 16
enum class eColliderLayer
{
	Default,
	Background, /// �ڿ� �׷��� �ֵ� ����..
	Tile,
	Player,
	Player_Projecttile,
	Monster,
	Monster_Projecttile,

	UI = _COLLIDER_LAYER - 1, /// ȭ�� ���� �տ� �׷�������
	End = _COLLIDER_LAYER,
};