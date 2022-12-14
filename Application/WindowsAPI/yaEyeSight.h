#pragma once
#include "yaGameObject.h"

namespace ya
{
	class EyeSight : public GameObject
	{
	public:
		EyeSight();
		~EyeSight();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		float mTime;
	};
}

