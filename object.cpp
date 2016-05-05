#include "object.h"

Object::Object():
    _pos(0, 0)
  , _texture(0)
  , _solid(true)
{

}

Object::~Object()
{

}

Object *Object::Clone()
{
    Object *o = new Object();
    o->_texture = _texture;
    o->_solid = _solid;
    return o;
}

void Object::SetPos(glm::vec2 pos)
{
    _pos = pos;
}

glm::vec2 Object::GetPos()
{
    return _pos;
}

void Object::SetTexture(GLuint texture)
{
    _texture = texture;
}

void Object::Draw(glm::vec2 pos, float size)
{
    glBindTexture(GL_TEXTURE_2D, _texture);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex2fv(&glm::vec2(pos.x - size, pos.y - size)[0]);
        glTexCoord2f(0,1);
        glVertex2fv(&glm::vec2(pos.x - size, pos.y + size * 3.f)[0]);
        glTexCoord2f(1,0);
        glVertex2fv(&glm::vec2(pos.x + size, pos.y - size)[0]);
        glTexCoord2f(1,1);
        glVertex2fv(&glm::vec2(pos.x + size, pos.y + size * 3.f )[0]);
    glEnd();
}

void Object::Update(float dt)
{

}

void Object::SetSolid(float solid)
{
    _solid = solid;
}

bool Object::IsSolid()
{
    return _solid;
}
