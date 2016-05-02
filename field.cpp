#include "field.h"
#include "glm/gtx/rotate_vector.hpp"



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
            DrawTile(i, j, 1);
        }
    }
}

void Field::DrawTile(int i, int j, GLuint texture)
{

    glm::vec2 pos = ToCell(i, j);
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


    for (auto o : _field[i][j])
    {
        auto pos = ToCell(o->GetPos());
        o->Draw(pos);
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
