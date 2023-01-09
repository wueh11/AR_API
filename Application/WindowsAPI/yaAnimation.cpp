#include "yaAnimation.h"
#include "yaImage.h"
#include "yaAnimator.h"
#include "yaGameObject.h"
#include "yaCamera.h"
#include "yaTime.h"

namespace ya
{
	Animation::Animation()
		:mbComplete(false)
	{
	}

	Animation::~Animation()
	{

	}

	void Animation::Tick()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();
		
		if (mSpriteSheet[mSpriteIndex].duration < mTime)
		{
			mTime = 0.0f;
			if (!mbReverse)
			{
				if (mSpriteSheet.size() <= mSpriteIndex + 1)
					mbComplete = true;
				else
					mSpriteIndex++;
			}
			else
			{ // 역재생
				if (mSpriteIndex == 0)
					mbComplete = true;
				else
					mSpriteIndex--;
			}
		}
	}
	
	void Animation::Render(HDC hdc)
	{
		GameObject* gameObj = mAnimator->GetOwner();

		Vector2 pos = gameObj->GetPos();
		Vector2 scale = gameObj->GetScale();
		Vector2 animatorOffset = mAnimator->GetOffset();

		if (mbAffectedCamera)
			pos = Camera::CalculatePos(pos); /// 카메라와 함께 이동하는 경우 ex)UI

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		pos += mSpriteSheet[mSpriteIndex].offset;

		/*AlphaBlend(hdc
			, int(pos.x + animatorOffset.x - (mSpriteSheet[mSpriteIndex].size.x / 2.0f)), int(pos.y + animatorOffset.y - (mSpriteSheet[mSpriteIndex].size.y / 2.0f))
			, int(mSpriteSheet[mSpriteIndex].size.x), int(mSpriteSheet[mSpriteIndex].size.y)
			, mImage->GetDC()
			, int(mSpriteSheet[mSpriteIndex].leftTop.x), int(mSpriteSheet[mSpriteIndex].leftTop.y)
			, int(mSpriteSheet[mSpriteIndex].size.x), int(mSpriteSheet[mSpriteIndex].size.y)
			, func);*/

		AlphaBlend(hdc
			, int(pos.x + (animatorOffset.x * scale.x) - (mSpriteSheet[mSpriteIndex].size.x * scale.x / 2.0f))
			, int(pos.y + (animatorOffset.y * scale.y) - (mSpriteSheet[mSpriteIndex].size.y * scale.y / 2.0f))
			, int(mSpriteSheet[mSpriteIndex].size.x * scale.x), int(mSpriteSheet[mSpriteIndex].size.y * scale.y)
			, mImage->GetDC()
			, int(mSpriteSheet[mSpriteIndex].leftTop.x), int(mSpriteSheet[mSpriteIndex].leftTop.y)
			, int(mSpriteSheet[mSpriteIndex].size.x), int(mSpriteSheet[mSpriteIndex].size.y)
			, func);

		pos += mSpriteSheet[mSpriteIndex].offset;

		/*TransparentBlt(hdc
			, int(pos.x + (animatorOffset.x * scale.x) - (mSpriteSheet[mSpriteIndex].size.x * scale.x / 2.0f))
			, int(pos.y + (animatorOffset.y * scale.y) - (mSpriteSheet[mSpriteIndex].size.y * scale.y / 2.0f))
			, int(mSpriteSheet[mSpriteIndex].size.x * scale.x), int(mSpriteSheet[mSpriteIndex].size.y * scale.y)
			, mImage->GetDC()
			, int(mSpriteSheet[mSpriteIndex].leftTop.x), int(mSpriteSheet[mSpriteIndex].leftTop.y)
			, int(mSpriteSheet[mSpriteIndex].size.x), int(mSpriteSheet[mSpriteIndex].size.y)
			, RGB(255, 0, 255));*/

		/*wchar_t szFloat[50] = {};
		std::wstring str = L"reverse: ";
		str += (mbReverse ? L"true" : L"false");
		swprintf_s(szFloat, 50, str.c_str());
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 300, 10, szFloat, strLen);*/
	}
	
	void Animation::Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration, bool bAffectedCamera, bool bVertical)
	{
		mImage = image;
		mbAffectedCamera = bAffectedCamera;
		mbVertical = bVertical;

		if (!bVertical)
		{
			for (size_t i = 0; i < spriteLength; i++)
			{
				Sprite sprite;
				sprite.leftTop.x = leftTop.x + (size.x * (float)i);
				sprite.leftTop.y = leftTop.y;
				sprite.size = size;
				sprite.offset = offset;
				sprite.duration = duration;

				mSpriteSheet.push_back(sprite);
			}
		}
		else
		{
			for (size_t i = 0; i < spriteLength; i++)
			{
				Sprite sprite;
				sprite.leftTop.x = leftTop.x;
				sprite.leftTop.y = leftTop.y + (size.y * (float)i);
				sprite.size = size;
				sprite.offset = offset;
				sprite.duration = duration;

				mSpriteSheet.push_back(sprite);
			}
		}
	}
	
	void Animation::Reset(bool bReverse)
	{
		mbReverse = bReverse;
		if (!bReverse)
			mSpriteIndex = 0;
		else
			mSpriteIndex = mSpriteSheet.size() - 1;

		mTime = 0.0f;
		mbComplete = false;
	}
}