#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"

namespace ya
{
	class Image;
	class Animator : public Component
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

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

	public:
		Animator();
		virtual ~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimation(std::wstring name, Image* image, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLength, float duration, bool bAffectedCamera = true);
		void Play(std::wstring name, bool bLoop = false);

		Animation* FindAnimation(std::wstring name);

		Events* FindEvents(const std::wstring key);

		std::function<void()>& GetStartEvent(const std::wstring key);
		std::function<void()>& GetCompleteEvent(const std::wstring key);
		std::function<void()>& GetEndEvent(const std::wstring key);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents; 

		Animation* mPlayAnimation;
		bool mbLoop; 
	};
}