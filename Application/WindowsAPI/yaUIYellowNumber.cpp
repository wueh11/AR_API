#include "yaUIYellowNumber.h"

#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	//std::wstring UIYellowNumber::Character[(UINT)UIYellowNumber::eCharacter::END]
	//{
	//	L"0", L"'1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9",
	//	L"P", L"U",
	//	//L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", L"T", L"U", L"V", L"W", L"X", L"Y", L"Z",
	//};

	UIYellowNumber::UIYellowNumber(eUIType type)
		: UIBase(type)
		, mCharacter(eCharacter::NUM_0)
	{
		SetSize({ 8.0f, 8.0f });

		/*for (size_t i = 0; i < (int)eCharacter::END; i++)
		{
			Image* image = Resources::Load<Image>(L"number_yellow_" + Character[i], L"number_yellow_" + Character[i] + L".bmp");
			mCharacters.insert(std::make_pair(Character[i], image));
		}*/
		//mImage = Resources::Load<Image>(L"number_yellow_0", L"..\\Resources\\Image\\UI\\player_upper_pistol.bmp");
	}
	
	UIYellowNumber::~UIYellowNumber()
	{
	}

	void UIYellowNumber::OnInit()
	{
	}

	void UIYellowNumber::OnActive()
	{
	}

	void UIYellowNumber::OnInActive()
	{
	}

	void UIYellowNumber::OnTick()
	{
		//mImage = mCharacters.find(mValue)->second;
	}

	void UIYellowNumber::OnRender(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER; ///blend옵션 AC_SRC_OVER: 원본이미지와 다른이미지를 섞는다
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; /// 투명도(alpha) 0~255

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void UIYellowNumber::OnClear()
	{
	}


}