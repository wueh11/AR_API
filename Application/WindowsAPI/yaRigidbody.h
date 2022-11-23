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
		// ���� �������� �̿��� �̵�
		float mMass;		/// ����
		Vector2 mForce;		/// ��ü�� �̴� ��
		Vector2 mVelocity;	/// ������ ���� �ӵ�
		Vector2 mAccelation;/// ���ӵ�
		float mFriction;	/// ������

		// �߷��� �̿��� ����
		Vector2 mGravity;	/// �߷� ũ��
		bool mbGround;		/// ���鿡 �پ��ִ���
		Vector2 mLimitVelocity;	/// �ӵ� �Ѱ谪
	};
}