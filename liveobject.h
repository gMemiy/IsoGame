#ifndef LIVEOBJECT_H
#define LIVEOBJECT_H

#include "object.h"

class LiveObject : public Object
{
public:
    LiveObject();
    virtual ~LiveObject();
    virtual void Update(float dt);

private:
    float _timer;
};

typedef QSharedPointer<LiveObject> LiveObjectPtr;
#endif // LIVEOBJECT_H
