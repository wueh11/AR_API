#pragma once
#include "Common.h"

namespace ya
{
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetPath() { return mPath; }
		const std::wstring& GetKey() { return mKey; }

		void SetPath(const std::wstring& path) { mPath = path; }
		void SetKey(const std::wstring& key) { mKey = key; }

	private:
		std::wstring mPath;
		std::wstring mKey;
	};
}

