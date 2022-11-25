#include "yaUIManager.h"

namespace ya
{
	std::unordered_map<eUIType, UIBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIBases;
	UIBase* UIManager::mCurrentData = nullptr;

	void UIManager::Initialize()
	{

	}

	void UIManager::Tick()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase != nullptr)
			{
				uiBase->Tick();
			}
			uiBases.pop();
		}

		if (mRequestUIQueue.size() > 0)
		{
			// UI Load
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();

			OnLoad(requestUI);
		}
	}

	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIBases; /// ���� ���ÿ��� ������ ����
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase != nullptr)
			{
				uiBase->Render(hdc);
			}
			uiBases.pop();
		}
	}

	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UIBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}

	void UIManager::OnComplete(UIBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Tick();

		if (addUI->IsFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases; /// ���� ���ÿ��� ������ ����
			while (!uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();
				uiBases.pop();

				if (uiBase->IsFullScreen())
					uiBase->InActive();
			}
		}

		mUIBases.push(addUI);
	}

	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}

	void UIManager::Release()
	{
		for (auto ui : mUIs)
		{
			delete ui.second;
			ui.second = nullptr;
		}
	}

	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}

	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		std::stack<UIBase*> tempStack;

		UIBase* uiBase = nullptr;
		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			// pop �ϴ� ui�� ��üȭ���� ��쿡, ���� ui�߿� ��üȭ���� ���� ����� ui�� Ȱ��ȭ ���־�� �Ѵ�.
			if (uiBase->GetType() == type)
			{
				if (uiBase->IsFullScreen())
				{
					std::stack<UIBase*> uiBases = mUIBases; /// ���� ���ÿ��� ������ ����
					while (!uiBases.empty())
					{
						UIBase* uiBase = uiBases.top();
						uiBases.pop();

						if (uiBase->IsFullScreen())
						{
							uiBase->Active();
							break;
						}
					}
				}
				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase);
			}
		}

		while (tempStack.size())
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}
	}
}