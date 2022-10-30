#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Rock : public GameObject
	{
	public:
		Rock();
		virtual ~Rock();

		virtual void Initialize() override;
		virtual void Tick();
		virtual void Render(HDC hdc);

	private:
		float mSpeed;
		
	};
}

