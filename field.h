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

struct Cell
{
    ~Cell();

    int GetValue();
    int GetObjectsCount();
    ObjectPtr GetObject(int index);
    void RemoveObject(ObjectPtr o);
    bool IsSolid();

    void SetValue(int val);
    void AddObject(ObjectPtr o);

    void Update(float dt);

private:

    void SolidUpdate();

    bool _isSolid = false;
    int _val = 0;
    std::list<ObjectPtr> _objects;
};


class Field
{
public:
    Field();
    Field(int sizeX, int sizeY);

    virtual ~Field();

    void Resize(int sizeX, int sizeY);

    int Value(int x, int y);
    bool IsValidIndex(int x, int y);

    int Height();
    int Width();

    void Update(float dt);

    protected:

    Cell &GetCell(int x, int y);

    int _sizeX;
    int _sizeY;
    std::vector<Cell> _field;
};


//typedef std::vector<std::list<ObjPtr>> Vector;

/*class Field
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
*/
#endif // FIELD_H
