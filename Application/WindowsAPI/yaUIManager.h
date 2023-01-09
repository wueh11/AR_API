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

		static void OnLoad(eUIType type); /// UI�� Load�� �� ȣ��
		static void OnComplete(UIBase* base); /// UI�� Load�Ϸ������
		static void OnFail(); /// UI �ε忡 ����������
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
		static std::unordered_map<eUIType, UIBase*> mUIs; /// �޸� �� �ö��ִ� UI
		static std::queue<eUIType> mRequestUIQueue; /// UI �޼���ť
		static std::stack<UIBase*> mUIBases;
		static UIBase* mCurrentData;	/// �������� �ִ� UI

		static bool mbActive;
	};
}

