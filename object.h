#ifndef OBJECT_H
#define OBJECT_H

#include "QtOpenGL"
#include "glm/glm.hpp"


class Object
{
public:

    Object();
    virtual ~Object();
    void SetPos(glm::vec2 pos);
    glm::vec2 GetPos();
    void SetTexture(GLuint texture);
    virtual void Draw(glm::vec2 pos, float size);
    virtual void Update(float dt);
    void SetSolid(float solid);
    bool IsSolid();

protected:

    bool _solid;
    GLuint _texture;
    glm::vec2 _pos;

};

typedef QSharedPointer<Object> ObjectPtr;

#endif // OBJECT_H
