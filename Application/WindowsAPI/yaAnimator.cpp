#include "yaAnimator.h"
#include "yaCamera.h"
#include "yaGameObject.h"
#include "yaResources.h" 
#include "yaImage.h"
#include "yaAnimation.h"

namespace ya
{
	Animator::Animator()
		:Component(eComponentType::Animator)
		, mPlayAnimation(nullptr)
		, mbLoop(false)
		, mOffset(Vector2::Zero)
	{
	}

	Animator::~Animator()
	{
		for (auto iter : mEvents)
		{
			delete iter.second;
		}

		for (auto iter : mAnimations)
		{
			delete iter.second;
		}
	}

	void Animator::Tick()
	{
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Tick();

			if (mbLoop && mPlayAnimation->isComplete())
			{
				Animator::Events* events = FindEvents(mPlayAnimation->getName());
				if (events != nullptr)
					events->mCompleteEvent();

				mPlayAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mPlayAnimation != nullptr)
			mPlayAnimation->Render(hdc);
	}

	void Animator::CreateAnimation(std::wstring name, Image* image, Vector2 leftTop, Vector2 size
			, Vector2 offset, UINT spriteLength, float duration, bool bAffectedCamera)
	{
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
		{
			MessageBox(nullptr, L"중복 키 애니메이션 생성", L"애니메이션 생성 실패!", MB_OK);
			return;
		}

		animation = new Animation();
		animation->Create(image, leftTop, size, offset, spriteLength, duration, bAffectedCamera);
		animation->SetName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}

	void Animator::Play(std::wstring name, bool bLoop)
	{
		Animator::Events* events = FindEvents(name);

		if (events != nullptr)
			events->mStartEvent();

		Animation* prevAnimation = mPlayAnimation;
		mPlayAnimation = FindAnimation(name);

		if(mPlayAnimation != nullptr)
		{
			mPlayAnimation->Reset();
			mbLoop = bLoop;

			if (prevAnimation != mPlayAnimation)
			{
				if (events != nullptr)
					events->mEndEvent();
			}
		}
	}

	Animation* Animator::FindAnimation(std::wstring name)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	Animator::Events* Animator::FindEvents(const std::wstring key)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(key);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);
		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);
		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);
		return events->mEndEvent.mEvent;
	}
}