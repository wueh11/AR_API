#include "yaEntity.h"

namespace ya
{
	Entity::Entity()
		: mName(L"")
		, mId((UINT32)this)
	{
	}
	Entity::~Entity()
	{
	}
}