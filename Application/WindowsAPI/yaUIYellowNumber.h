#pragma once
#include "yaUIBase.h"

namespace ya
{
	class UIYellowNumber : public UIBase
	{
	public:
		enum class eCharacter
		{
			NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
			P, U,
			//A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			END,
		};

	public:
		UIYellowNumber(eUIType type);
		virtual ~UIYellowNumber();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		//std::wstring Character[(UINT)UIYellowNumber::eCharacter::END];

	public:
		void SetNumber(eCharacter ch) { mCharacter = ch; }

	private:
	//	static std::unordered_map<std::wstring, Image*> mCharacters;

		std::wstring mValue;
		eCharacter mCharacter;
	};
}

