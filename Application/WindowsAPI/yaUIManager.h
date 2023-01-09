#pragma once
#include "Common.h"
#include "yaUIBase.h"

namespace ya
{
	class UIManager
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static void OnLoad(eUIType type); /// UI를 Load할 때 호출
		static void OnComplete(UIBase* base); /// UI가 Load완료됐을대
		static void OnFail(); /// UI 로드에 실패했을때
		static void Release();

		static void Push(eUIType type);
		static void Pop(eUIType type);

		template <typename T>
		static T* GetUIInstant(eUIType type)
		{
			return dynamic_cast<T*>(mUIs[type]);
		}

		static void SetActive(bool active) { mbActive = active; }

	private:
		static std::unordered_map<eUIType, UIBase*> mUIs; /// 메모리 상에 올라가있는 UI
		static std::queue<eUIType> mRequestUIQueue; /// UI 메세지큐
		static std::stack<UIBase*> mUIBases;
		static UIBase* mCurrentData;	/// 마지막에 있는 UI

		static bool mbActive;
	};
}

