#include "yaComponent.h"

namespace ya
{
    Component::Component(eComponentType type)
        :mType(type)
    {
    }
    Component::~Component()
    {
    }
    void Component::Tick()
    {
    }
    void Component::Render(HDC hdc)
    {
    }
}