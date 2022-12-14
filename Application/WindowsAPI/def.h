#pragma once

#define W_WIDTH 800 
#define W_HEIGHT 600 

#define M_SCALE 2.6f

#define KEY_PRESS(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::PRESSED
#define KEY_DOWN(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::DOWN
#define KEY_UP(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::UP

enum class eSceneType
{
	Logo,
	Select,
	//Play,
	Mission1,
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
	Rigidbody,
	Collider,
	Animator,
	Sound,
	End,
};

#define _COLLIDER_LAYER 16
enum class eColliderLayer
{
	Default,
	Background_pixel,
	Background, /// 뒤에 그려질 애들 먼저..
	MapObject, //background 앞에 그려질 오브젝트
	Event, // 이벤트 발생 지점

	Item,
	Player,
	Player_Projecttile,
	Monster,

	Monster_Projecttile,
	Collider, // 충돌이 적용되는 object collider

	Background_front, /// 플레이어를 가리는 배경
	Effect,
	
	UI = _COLLIDER_LAYER - 1, /// 화면 제일 앞에 그려져야함
	End = _COLLIDER_LAYER,
};

enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
};

enum class eUIType
{
	LIFE,
	HP,
	INVENTORY,
	SCORE,
	TIME,
	OPTION,

	END,
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

enum class eArms
{
	Pistol,
	HeavyMachinegun,
	ShotGun,
	LaserGun,

	END,
};