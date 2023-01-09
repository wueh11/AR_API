#include "yaArmsCount.h"
#include "yaImage.h"

#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaPlayer.h"

#include "yaAnimator.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	ArmsCount::ArmsCount()
	{
		SetPos({0.0f, 0.0f});
		SetSize({ 8.0f, 8.0f });
		SetScale({ M_SCALE, M_SCALE });

		if (mImage == nullptr)
			mImage = Resources::Load<Image>(L"text_yellow", L"..\\Resources\\Image\\UI\\text_yellow.bmp");

		for (size_t i = 0; i < 3; i++)
		{
			mAnimator[i] = new Animator();

			mAnimator[i]->CreateAnimation(L"text_yellow_empty", mImage, Vector2(100.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_0", mImage, Vector2(1.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_1", mImage, Vector2(10.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_2", mImage, Vector2(19.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_3", mImage, Vector2(28.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_4", mImage, Vector2(37.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_5", mImage, Vector2(46.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_6", mImage, Vector2(55.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_7", mImage, Vector2(64.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_8", mImage, Vector2(73.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_9", mImage, Vector2(82.0f, 19.0f), Vector2(8.0f, 8.0f), Vector2(0.0f, 0.0f), 1, 1.0f, false);
			mAnimator[i]->CreateAnimation(L"text_yellow_nolimit", mImage, Vector2(1.0f, 28.0f), Vector2(20.0f, 8.0f), Vector2(20.0f, 0.0f), 1, 1.0f, false);

			mAnimator[i]->Play(L"text_yellow_empty");
			mAnimator[i]->SetOffset({ 8.0f * i, 0.0f });

			AddComponent(mAnimator[i]);
		}
	}

	ArmsCount::~ArmsCount()
	{
	}

	void ArmsCount::Initialize()
	{
	}

	void ArmsCount::Tick()
	{
		GameObject::Tick();

		Scene* scene = SceneManager::GetPlayScene();
		Player* player = scene->GetPlayer();

		if (player->GetInfo().arms == eArms::Pistol)
		{
			mAnimator[0]->Play(L"text_yellow_nolimit");
			mAnimator[1]->Play(L"text_yellow_empty");
			mAnimator[2]->Play(L"text_yellow_empty");

		}
		else
		{
			int armsCount = player->GetInfo().armsCount;
			int num[3] = { -1, -1, 0 };

			{
				if (armsCount / 100 > 0)
				{
					num[0] = armsCount / 100;
					armsCount = armsCount % 100;
				}

				if (armsCount == 0)
				{
					num[1] = 0;
				}
				else if (armsCount / 10 > 0)
				{
					num[1] = armsCount / 10;
				}

				num[2] = armsCount % 10;
			}

			for (size_t i = 0; i < 3; i++)
			{
				if (num[i] >= 0)
					mAnimator[i]->Play(L"text_yellow_" + std::to_wstring(num[i]));
				else
					mAnimator[i]->Play(L"text_yellow_empty");
			}
		}
	}

	void ArmsCount::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


}