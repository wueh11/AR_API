#pragma once
class PlayerKnife
{
};

#pragma once
#include "yaGameObject.h"

namespace ya
{
	class PlayerKnife : public GameObject
	{
	public:
		PlayerKnife();
		~PlayerKnife();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	public:
		void SetActive(bool active) { mbActive = active; }

	private:
		float mTime;
		float mAliveTime;
		bool mbActive;
	};
}

