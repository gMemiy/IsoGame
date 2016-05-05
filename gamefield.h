#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "field.h"



class GameField : public Field
{
public:

    GameField();
    GameField(int x, int y);
    void Draw();

    void SetFloorTexture(GLuint texture);
    void SetAngle(float angle);

    glm::vec2 GetCellPos(int i, int j);
    QPoint GetCellByPos(float x, float y);
    void SetCellSize(float cellSize);

private:

    GLuint _floorTexture;
    float _angle;
    float _cellSize;
};

#endif // GAMEFIELD_H
