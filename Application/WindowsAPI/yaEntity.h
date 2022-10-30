#pragma once
#include "Common.h"

namespace ya
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring name) { mName = name; }
		std::wstring getName() { return mName; }

	private:
		std::wstring mName;
		UINT mId;
	};
}