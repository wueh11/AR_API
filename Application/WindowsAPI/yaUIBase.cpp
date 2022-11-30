#include "yaUIBase.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	UIBase::UIBase(eUIType type)
		: mType(type)
		, mbFullScreen(false)
		, mbEnable(false)
		, mParent(nullptr)
		, mPos(Vector2::Zero)
		, mSize(Vector2::Zero)
	{
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		OnInit();

		for (UIBase* child : mChildren)
		{
			child->OnInit();
		}
	}

	void UIBase::Active()
	{
		mbEnable = true;
		OnActive();

		for (UIBase* child : mChildren)
		{
			child->mbEnable = true;
			child->OnActive();
		}
	}

	void UIBase::InActive()
	{
		for (UIBase* child : mChildren)
		{
			child->OnInActive();
			child->mbEnable = false;
		}

		OnInActive();
		mbEnable = false;
	}

	void UIBase::Tick()
	{
		if (!mbEnable)
			return;

		OnTick();

		if (mParent)
			/// 부모가 있다면 스크린좌표를 부모 기준으로 설정
			mScreenPos = mParent->GetPos() + mPos;
		else
			mScreenPos = mPos;

		for (UIBase* child : mChildren)
		{
			if (child->mbEnable)
				child->Tick();
		}
	}

	void UIBase::Render(HDC hdc)
	{
		if (!mbEnable)
			return;

		OnRender(hdc);
		for (UIBase* child : mChildren)
		{
			if (child->mbEnable)
				child->Render(hdc);
		}
	}

	void UIBase::UIClear()
	{
		for (UIBase* child : mChildren)
		{
			if (child->mbEnable)
				child->OnClear();
		}

		OnClear();
	}

	void UIBase::ImageLoad(const std::wstring& key, const std::wstring& path)
	{
		mImage = Resources::Load<Image>(key, path);
		SetSize(Vector2(mImage->GetWidth(), mImage->GetHeight()));
	}

	void UIBase::AddChild(UIBase* uiBase)
	{
		mChildren.push_back(uiBase);
		uiBase->mParent = this;
	}
}