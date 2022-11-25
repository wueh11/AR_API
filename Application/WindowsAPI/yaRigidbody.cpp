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

		// �ӵ��� ���ӵ��� �����ش�.
		mVelocity += (mAccelation * Time::DeltaTime());

		if (mbGround)
		{ // ��
			Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = math::Dot(mVelocity, gravity); /// ���⿡ ���� �߷� ũ�� ������
			mVelocity -= gravity * dot;
		}
		else
		{ // ����
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

		// ������ ���� : ����� ���� ����, �ӵ��� 0�� �ƴҶ�
		if (!(mVelocity == Vector2::Zero))
		{
			// �ӵ��� �ݴ� ����
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.Length() < friction.Length())
				// �ӵ��� 0 �� �����.
				mVelocity = Vector2::Zero;
			else
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				mVelocity += friction;
		}

		// �ӵ��� ���� ��ü�� �̵���Ų��.
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