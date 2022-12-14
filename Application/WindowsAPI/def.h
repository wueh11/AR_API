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

enum class eComponentType ///������Ʈ ������
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
	Background, /// �ڿ� �׷��� �ֵ� ����..
	MapObject, //background �տ� �׷��� ������Ʈ
	Event, // �̺�Ʈ �߻� ����

	Player,
	Player_Projecttile,
	Monster,
	Monster_Projecttile,
	Collider, // �浹�� ����Ǵ� object collider

	Background_front, /// �÷��̾ ������ ���
	Effect,
	
	UI = _COLLIDER_LAYER - 1, /// ȭ�� ���� �տ� �׷�������
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
	HP,
	MP,
	SHOP,
	INVENTORY,
	OPTION,

	END,
};

union ColliderID ///union -> �޸� ������ ������ �����Ѵ�
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