#pragma once
#include "Common.h"

namespace ya
{
	class Scene;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);
		static void DestroyGameObject();
		static void Release();

		static void ChangeScene(eSceneType type);

		static Scene* GetPlayScene() { return mPlayScene; }
		static void SetPlayScene(Scene* playScene) { mPlayScene = playScene; }

		static Scene* GetScene(eSceneType type) { return mScenes[(UINT)type]; }
		static eSceneType GetPlaySceneType() { return mType; }

	private:
		static Scene* mScenes[(UINT)eSceneType::MAX];

		static Scene* mPlayScene;
		static eSceneType mType;
	};
}