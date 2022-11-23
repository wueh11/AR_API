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

		void Initialize();	// UI가 로드 되었을 때 불리는 초기화 함수 (메모리에 올라왔을 때)
		void Tick();		// UI가 업데이트 될 때마다 호출되는 함수
		void Render(HDC hdc);

		void Active();		// UI가 활성화 되면 불리는 함수
		void InActive();	// UI가 비활성화 되면 불리는 함수
		void UIClear();		// UI가 사라질 때 호출되는 함수 (메모리에서 삭제될 때)

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
		virtual void OnInit() {};	// 초기화
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnTick() {};
		virtual void OnRender(HDC hdc) {};
		virtual void OnClear() {};
		virtual void Onclick() {};

	protected:
		UIBase* mParent;

		Image* mImage;
		Vector2 mPos;	/// 창 위치
		Vector2 mSize;	/// 창 크기
		Vector2 mScreenPos;

	private:
		std::vector<UIBase*> mChildren;
		eUIType mType;
		bool mbFullScreen; /// 전체화면인지
		bool mbEnable;
	};
}
