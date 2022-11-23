#pragma once
#include "yaComponent.h"

namespace ya
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		bool isGround() { return mbGround; }

		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }

	private:
		// 힘과 마찰력을 이용한 이동
		float mMass;		/// 무게
		Vector2 mForce;		/// 물체는 미는 힘
		Vector2 mVelocity;	/// 방향을 갖는 속도
		Vector2 mAccelation;/// 가속도
		float mFriction;	/// 마찰력

		// 중력을 이용한 점프
		Vector2 mGravity;	/// 중력 크기
		bool mbGround;		/// 지면에 붙어있는지
		Vector2 mLimitVelocity;	/// 속도 한계값
	};
}