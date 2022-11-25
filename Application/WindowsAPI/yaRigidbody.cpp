#include "yaRigidbody.h"

#include "yaTime.h"
#include "yaGameObject.h"

namespace ya
{
	Rigidbody::Rigidbody()
		:Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mForce(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mFriction(100.0f)
	{
		mGravity = Vector2(0.0f, 800.0f);
		mbGround = false;
		mLimitVelocity = Vector2(200.0f, 1000.0f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Tick()
	{
		if (mMass == 0.0f)
			return;

		mAccelation = mForce / mMass;

		// 속도에 가속도를 더해준다.
		mVelocity += (mAccelation * Time::DeltaTime());

		if (mbGround)
		{ // 땅
			Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = math::Dot(mVelocity, gravity); /// 방향에 따른 중력 크기 내적값
			mVelocity -= gravity * dot;
		}
		else
		{ // 공중
			mVelocity += mGravity * Time::DeltaTime();
		}

		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}

		mVelocity = gravity + sideVelocity;

		// 마찰력 조건 : 적용된 힘이 없고, 속도가 0이 아닐때
		if (!(mVelocity == Vector2::Zero))
		{
			// 속도에 반대 방향
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.Length() < friction.Length())
				// 속도를 0 로 만든다.
				mVelocity = Vector2::Zero;
			else
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
		}

		// 속도에 맞춰 물체를 이동시킨다.
		Vector2 pos = GetOwner()->GetPos();
		pos += mVelocity * Time::DeltaTime();

		GetOwner()->SetPos(pos);
		mForce.Clear();
	}

	void Rigidbody::Render(HDC hdc)
	{
		wchar_t szFloat[50] = {};

		std::wstring strForce = L"Force : " + std::to_wstring(mForce.x) + L", " + std::to_wstring(mForce.y);
		swprintf_s(szFloat, 50, strForce.c_str());
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 1050, 30, szFloat, strLen);

		std::wstring strVelocity = L"Velocity : " + std::to_wstring(mVelocity.x) + L", " + std::to_wstring(mVelocity.y);
		swprintf_s(szFloat, 50, strVelocity.c_str());
		TextOut(hdc, 1050, 50, szFloat, strLen);

		std::wstring isGround = (mbGround ? L"TRUE" : L"FALSE");
		std::wstring strGround = L"Ground : " + isGround;
		swprintf_s(szFloat, 50, strGround.c_str());
		TextOut(hdc, 1050, 70, szFloat, strLen);
	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}