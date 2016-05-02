#ifndef LIVEOBJECT_H
#define LIVEOBJECT_H

#include "object.h"

class LiveObject : public Object
{
public:
    LiveObject();
    virtual ~LiveObject();
    virtual void Update(float dt);

    void SetSpeed(int sx, int sy);
    float GetTimer();

private:
    float _timer;
    glm::vec2 _speed;
};

typedef QSharedPointer<LiveObject> LiveObjectPtr;
#endif // LIVEOBJECT_H
