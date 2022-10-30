#include "yaGameObject.h"

namespace ya
{
	GameObject::GameObject()
		:mPos(Vector2(0.0f, 0.0f))
		, mScale{ 1.0f, 1.0f }
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
		//��� ������Ʈ Tick ȣ��
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Tick();
		}
	}
	void GameObject::Render(HDC hdc)
	{
		//��� ������Ʈ Render ȣ��
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Render(hdc);
		}
	}

	void GameObject::AddComponent(Component* component)
	{
		if (component == nullptr)
			return;

		mComponents.push_back(component);
		component->mOwner = this;
	}
}