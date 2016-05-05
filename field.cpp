#include "field.h"



Cell::~Cell()
{
    _objects.clear();
}

int Cell::GetValue()
{
    return _val;
}
int Cell::GetObjectsCount()
{
    return _objects.size();
}

ObjectPtr Cell::GetObject(int index)
{
    if (index >= 0 && index < _objects.size())
    {
        auto o = _objects.begin();

        for (int i = 0;  i < index; ++i, ++o);

        return *(o);
    }
    return ObjectPtr(nullptr);
}
void Cell::RemoveObject(ObjectPtr o)
{
    _objects.remove(o);
    SolidUpdate();
}
bool Cell::IsSolid()
{
    return _isSolid;
}

void Cell::SetValue(int val)
{
    _val = val;
}
void Cell::AddObject(ObjectPtr o)
{
    _isSolid = _isSolid || o->IsSolid();
    _objects.push_back(o);
}

void Cell::SolidUpdate()
{
    _isSolid = false;
    for (auto o : _objects)
    {
        _isSolid = _isSolid || o->IsSolid();
        if (_isSolid)
        {
            break;
        }
    }
}

void Cell::Update(float dt)
{
    for (auto o : _objects)
    {
        o->Update(dt);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




Field::Field():
    _sizeX(0)
  , _sizeY(0)
{

}
Field::Field(int sizeX, int sizeY):
    _sizeX(sizeX)
  , _sizeY(sizeY)
{
    Resize(sizeX, sizeY);
}

void Field::Resize(int sizeX, int sizeY)
{
    if (sizeX <= 0 && sizeY <= 0)
    {
        _sizeX = std::max(0, _sizeX);
        _sizeY = std::max(0, _sizeY);
    }
    else
    {
        _sizeX = sizeX;
        _sizeY = sizeY;

        int size = _sizeX * _sizeY;

        _field.clear();
        _field.reserve(size);
        _field.resize(size);
    }
}


Field::~Field()
{
    _field.clear();
}

int Field::Value(int x, int y)
{
    if (IsValidIndex(x, y))
    {
        return GetCell(x, y).GetValue();
    }
    return -1;
}
bool Field::IsValidIndex(int x, int y)
{
    return x >= 0 && x < _sizeX && y >= 0 && y < _sizeY;
}

Cell &Field::GetCell(int x, int y)
{
    return _field[_sizeX * x + y];
}

int Field::Height()
{
    return _sizeX;
}

int Field::Width()
{
    return _sizeY;
}

void Field::Update(float dt)
{
    for (auto c : _field)
    {
        c.Update(dt);
    }
}

/*
glm::vec2 Field::ToCell(float x, float y, bool mul)
{
    float f = 1;
    if (mul == 0)
    {
        f = -1;
    }
    auto buf = glm::rotateZ(glm::vec3(x, y, 0),  f * 45.f / 180.f * 3.14f);
    return glm::vec2(buf.x, buf.y);
}

glm::vec2 Field::ToCell(glm::vec2 pos, bool mul)
{

    return ToCell(pos.x, pos.y, mul);
}

Field::Field():
    _size(30)
{
    _field.reserve(_size.x);
    _field.resize(_size.x);
    for (int i = 0; i < _size.x; ++i)
    {
        _field[i].reserve(_size.y);
        _field[i].resize(_size.y);
        for (int j = 0; j < _size.y; ++j)
        {
     //       AddObject(i, j);
        }
    }
}

void Field::Draw()
{

    for (int i = _size.x - 1; i >= 0; --i)
    {
        for (int j = _size.y - 1; j >= 0; --j)
        {
            glm::vec2 pos = ToCell(i, j);
            float size = .7f;
            {
                glColor3f(1,1,1);
            }
            glBindTexture(GL_TEXTURE_2D, 1);
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
    }



    for (int i = _size.x - 1; i >= 0; --i)
    {
        for (int j = _size.y - 1; j >= 0; --j)
        {
            DrawTile(i, j, 1);
        }
    }
}

void Field::DrawTile(int i, int j, GLuint texture)
{

   /* glm::vec2 pos = ToCell(i, j);
    float size = .7f;
    {
        glColor3f(1,1,1);
    }
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex2fv(&glm::vec2(pos.x - size, pos.y - size)[0]);
        glTexCoord2f(0,1);
        glVertex2fv(&glm::vec2(pos.x - size, pos.y + size * 3.f)[0]);
        glTexCoord2f(1,0);glm::vec2 pos = ToCell(i, j);
        float size = .7f;
        {
            glColor3f(1,1,1);
        }
        glBindTexture(GL_TEXTURE_2D, texture);
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
        glVertex2fv(&glm::vec2(pos.x + size, pos.y - size)[0]);
        glTexCoord2f(1,1);
        glVertex2fv(&glm::vec2(pos.x + size, pos.y + size * 3.f )[0]);
    glEnd();


    for (auto o : _field[i][j])
    {
        auto pos = ToCell(i, j);
        auto dp = ToCell(((LiveObject*)(&(*o)))->GetTimer() - 0.5f, 0);
        o->Draw(pos + dp);
    }
}


bool Field::IsValidIndexs(int i, int j)
{
    return i >= 0 && j >= 0 &&  i < _size.x && j < _size.y;
}

void Field::AddObject(int i, int j)
{
    if (IsValidIndexs(i, j))
    {
        LiveObjectPtr o = LiveObjectPtr(new LiveObject());
        o->SetPos(glm::vec2(i, j));
        o->SetSolid(true);
        o->SetTexture(2);
        _field[i][j].push_back(o);
    }
}

void Field::Click(int i, int j)
{
    if (IsValidIndexs(i, j))
    {
        if (_field[i][j].size() > 0)
        {
            _field[i][j].clear();
        }
        else
        {
            AddObject(i, j);
        }
    }
}

void Field::Update(float dt)
{
    for (auto v : _field)
    {
        for (auto l : v)
        {
            for (auto o : l)
            {
                o->Update(dt);
            }
        }
    }


    for (int i = 0; i < _size.x; ++i)
    {
        for (int j = 0; j < _size.x; ++j)
        {
            for (auto o = _field[i][j].begin(); o != _field[i][j].end();)
            {
                auto p = (*o)->GetPos();
                glm::vec2 pos(round(p.x), round(p.y));
                if ((pos.x != i || pos.y != j) && IsValidIndexs(pos.x, pos.y))
                {
                    _field[pos.x][pos.y].push_back(*o);
                    o = _field[i][j].erase(o);
                }
                else
                {
                    if (!IsValidIndexs(pos.x, pos.y))
                    {
                        (*o)->SetPos(glm::vec2(i, j));
                    }
                    ++o;
                }
            }
        }
    }
}
*/
