#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	GameObject::GameObject()
		: mPos(Vector2(0.0f, 0.0f))
		, mScale{ 1.0f, 1.0f }
		, mSize{ 0.0f, 0.0f }
		, mDead(false)
		, mDeathTime(-100.0f)
		, mOwner(nullptr)
	{
	}

	GameObject::~GameObject()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			delete component;
			component = nullptr;
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Tick()
	{
		DeathLoop();

		//모든 컴포넌트 Tick 호출
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Tick();

			for (GameObject* child : mChildren)
 				child->Tick();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		//모든 컴포넌트 Render 호출
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Render(hdc);
		}

		for (GameObject* child : mChildren)
			child->Render(hdc);
	}

	void GameObject::OnCollisionEnter(Collider* other)
	{
	}

	void GameObject::OnCollisionStay(Collider* other)
	{
	}

	void GameObject::OnCollisionExit(Collider* other)
	{
	}

	void GameObject::AddChild(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mChildren.push_back(gameObject);
		gameObject->mOwner = this;
	}

	void GameObject::AddComponent(Component* component)
	{
		if (component == nullptr)
			return;

		mComponents.push_back(component);
		component->mOwner = this;
	}

	void GameObject::SetDeathTime(float time)
	{
		if(mDeathTime <= 0.0f)
		{
			mDeathTime = time;
		}
	}

	void GameObject::DeathLoop()
	{
		if (mDeathTime == true)
		{
			mDeathTime -= Time::DeltaTime();

			if (mDeathTime <= 0.0f)
				Death();
		}
	}
}