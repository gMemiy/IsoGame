#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QtOpenGL>
#include "glm/glm.hpp"

#include "gamefield.h"

class Scene : public QGLWidget // класс для работы с  окном
{
    Q_OBJECT
public:
    Scene(QWidget *parent = 0);

public slots:
    void Update();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *pe);

    void DrawTile(glm::vec2 pos, GLuint texture);
private:

    glm::vec2 ScreenToWorld(QPoint p); // перевод оконнх координат в координаты сцены
    void DrawBackGround(GLuint texture); // рисует прямоугольник на весь экран, с заданной текстурой

    float GetDt();
    void UpdateStatistic(float dt);

    GLuint InitTexture(QString path); // загрузка текстуры из файла
    void InitFireWork();


    // размеры сцены
    glm::vec2 _hor; // горизонталь
    glm::vec2 _vert; // вертикаль
    glm::vec2 _depth; // глубина

    glm::vec2 _mousePos;

    GLuint _tile;
    GLuint _floor;

    GameField _f;

    QSharedPointer<QTime> _timer;
    float _oldTime;
    int _fps;
    float _sec;

};

#endif // SCENE_H
