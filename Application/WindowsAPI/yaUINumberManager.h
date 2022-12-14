#pragma once
#include "Common.h"

namespace ya
{
	enum class eCharacter
	{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
		TIME, LEVEL,
		End,
	};

	class Image;
	class UINumberManager
	{
	public:
		static void Initialize();

		static Image* GetImage(eCharacter eCharacter);

	private:
		static std::unordered_map<eCharacter, Image*> mCharacters;
	};
}

