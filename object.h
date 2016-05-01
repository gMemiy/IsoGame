#ifndef OBJECT_H
#define OBJECT_H

#include "QtOpenGL"
#include "glm/glm.hpp"


class Object
{
public:

    Object();
    void SetPos(glm::vec2 pos);
    glm::vec2 GetPos();
    void SetTexture(GLuint texture);
    void Draw();
    void Update(float dt);
    void SetSolid(float solid);
    bool IsSolid();

private:

    bool _solid;
    GLuint _texture;
    glm::vec2 _pos;

};

#endif // OBJECT_H
