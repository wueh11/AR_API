#pragma once
#include "yaEntity.h"

namespace ya
{
	class Image;
	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};

	public:
		UIBase(eUIType type);
		virtual ~UIBase();

		void Initialize();	// UI�� �ε� �Ǿ��� �� �Ҹ��� �ʱ�ȭ �Լ� (�޸𸮿� �ö���� ��)
		void Tick();		// UI�� ������Ʈ �� ������ ȣ��Ǵ� �Լ�
		void Render(HDC hdc);

		void Active();		// UI�� Ȱ��ȭ �Ǹ� �Ҹ��� �Լ�
		void InActive();	// UI�� ��Ȱ��ȭ �Ǹ� �Ҹ��� �Լ�
		void UIClear();		// UI�� ����� �� ȣ��Ǵ� �Լ� (�޸𸮿��� ������ ��)

		void ImageLoad(const std::wstring& key, const std::wstring& path);

	public:
		void AddChild(UIBase* uiBase);
		void SetParent(UIBase* parent) { mParent = parent; }

		eUIType GetType() { return mType; }

		bool IsFullScreen() { return mbFullScreen; }
		void SetFullScreen(bool enable) { mbFullScreen = enable; }

		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() { return mPos; }

		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetSize() { return mSize; }

		void SetScreenPos(Vector2 screenPos) { mScreenPos = screenPos; }
		Vector2 GeScreentPos() { return mScreenPos; }

	private:
		virtual void OnInit() {};	// �ʱ�ȭ
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnTick() {};
		virtual void OnRender(HDC hdc) {};
		virtual void OnClear() {};
		virtual void Onclick() {};

	protected:
		UIBase* mParent;

		Image* mImage;
		Vector2 mPos;	/// â ��ġ
		Vector2 mSize;	/// â ũ��
		Vector2 mScreenPos;

	private:
		std::vector<UIBase*> mChildren;
		eUIType mType;
		bool mbFullScreen; /// ��üȭ������
		bool mbEnable;
	};
}
