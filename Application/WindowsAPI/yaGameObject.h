#pragma once
#include "Common.h"
#include "yaEntity.h"
#include "yaComponent.h"

namespace ya
{
	struct info
	{
		UINT hp;
	};
	
	class Collider;
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize() = 0;
		virtual void Tick() = 0;
		virtual void Render(HDC hdc) = 0;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() { return mPos; }

		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() { return mScale; }

		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetSize() { return mSize; }

		void Death() { mDead = true; }
		bool IsDeath() { return mDead; }
		void SetDeathTime(float time);

		void DeathLoop();

		void AddComponent(Component* component);

		template <typename T>
		__forceinline T* AddComponent()
		{
			T* comp = new T();
			GameObject::AddComponent(comp);

			return comp;
		}

		template<typename T>
		__forceinline T* GetComponent()
		{
			T* component;
			for (Component* c : mComponents)
			{
				component = dynamic_cast<T*>(c);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		ObjectInfo GetObjectInfo() { return mObjectInfo; }

	private:
		std::vector<Component*> mComponents;
		Vector2 mPos;
		Vector2 mScale;
		Vector2 mSize;

		bool mDead;
		float mDeathTime;
		bool mDeathTimeOn;

		ObjectInfo mObjectInfo;
	};
}


