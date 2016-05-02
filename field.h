#ifndef FIELD_H
#define FIELD_H

#include "object.h"
#include "liveobject.h"

#include <vector>
#include <glm/glm.hpp>
#include "QtOpenGL"

enum Type
{
    Busy,
    Free
};



typedef std::vector<std::list<ObjPtr>> Vector;

class Field
{
public:
    Field();
    void Draw();
    void DrawTile(int i, int j, GLuint texture);
    void AddObject(int i, int j);
    void Click(int i, int j);
    bool IsValidIndexs(int i, int j);
    void Update(float dt);

    static glm::vec2 ToCell(float x, float y, bool mul = 1);
    static glm::vec2 ToCell(glm::vec2 pos, bool mul = 1);

private:
    glm::vec2 _size;
    std::vector<Vector> _field;
};

#endif // FIELD_H
