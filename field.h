#ifndef FIELD_H
#define FIELD_H

#include "object.h"

#include <vector>
#include <glm/glm.hpp>
#include "QtOpenGL"

enum Type
{
    Busy,
    Free
};



typedef std::vector<std::list<Object>> Vector;

class Field
{
public:
    Field();
    void Draw();
    void DrawTile(int i, int j, GLuint texture);
    void AddObject(int i, int j);
    bool IsValidIndexs(int i, int j);

private:
    glm::vec2 _size;
    std::vector<Vector> _field;
};

#endif // FIELD_H
