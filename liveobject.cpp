#include "liveobject.h"

LiveObject::LiveObject():
    _timer(0.f)
{

}

LiveObject::~LiveObject()
{

}

void LiveObject::Update(float dt)
{
    _timer += dt;
    if (_timer >= 1.f)
    {
        _pos.x += 1;
        _timer -= 1.f;
    }
}
