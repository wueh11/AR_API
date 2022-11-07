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

enum class eComponentType ///컴포넌트 종류들
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
	Background, /// 뒤에 그려질 애들 먼저..
	Tile,
	Player,
	Player_Projecttile,
	Monster,
	Monster_Projecttile,

	Backpack,
	UI = _COLLIDER_LAYER - 1, /// 화면 제일 앞에 그려져야함
	End = _COLLIDER_LAYER,
};

enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
};

union ColliderID ///union -> 메모리 데이터 영역을 공유한다
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};
	UINT64 ID;
};