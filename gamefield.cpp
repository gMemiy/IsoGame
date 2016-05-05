#include "gamefield.h"
#include "glm/gtx/rotate_vector.hpp"

GameField::GameField(): Field()
  , _floorTexture(0)
  , _angle(0)
  , _cellSize(1)
{

}



GameField::GameField(int x, int y): Field(x, y)
  , _floorTexture(0)
  , _angle(0)
  , _cellSize(1)
{

}

void GameField::Draw()
{
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, _floorTexture);

    float size = .7f * _cellSize;
    for (int i = _sizeX - 1; i >= 0; --i)
    {
        for (int j = _sizeY - 1; j >= 0; --j)
        {
            glm::vec2 pos = GetCellPos(i, j);

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



    for (int i = _sizeX - 1; i >= 0; --i)
    {
        for (int j = _sizeY - 1; j >= 0; --j)
        {
            Cell c = GetCell(i, j);
            int oCount = c.GetObjectsCount();
            glm::vec2 pos = GetCellPos(i, j);
            for (int l = 0; l < oCount; ++l)
            {
                c.GetObject(l)->Draw(pos, size);
            }
        }
    }
}

void GameField::SetFloorTexture(GLuint texture)
{
    _floorTexture = texture;
}

void GameField::SetAngle(float angle)
{
    _angle = angle;
}

glm::vec2 GameField::GetCellPos(int i, int j)
{
    auto buf = glm::rotateZ(glm::vec3(i * _cellSize, j * _cellSize, 0),  _angle / 180.f * 3.14f);
    return glm::vec2(buf.x, buf.y);
}

QPoint GameField::GetCellByPos(float x, float y)
{
    auto buf = glm::rotateZ(glm::vec3(x, y, 0),  -_angle / 180.f * 3.14f);
    return QPoint(round(buf.x / _cellSize), round(buf.y / _cellSize));
}

void GameField::SetCellSize(float cellSize)
{
    if (cellSize > 0)
    {
        _cellSize = cellSize;
    }
}
