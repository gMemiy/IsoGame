#include "scene.h"
#include "glm/gtx/rotate_vector.hpp"

Scene::Scene(QWidget *parent) : QGLWidget(parent)
{
    resize(1024, 768);
    _timer = QSharedPointer<QTime>(new QTime());
    _timer->start();
    _oldTime = (float)_timer->msecsTo(QTime::currentTime()) / 1000.f;

    _sec = 0;
    _fps = 0;
}

void Scene::initializeGL()
{

    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);

    // настраиваем фейерверк и облака
    InitFireWork();

    _floor = InitTexture("images/floor.png");
    _tile = InitTexture("images/wall.png");

    _f.AddObject(1,1);

}

void Scene::resizeGL(int w, int h) // изменение размера
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float r = w / h;

    _hor = glm::vec2(-30, 30);
    _vert = glm::vec2(-5, 45);
    _depth = glm::vec2(2, -2);

    glOrtho(_hor.x, _hor.y, _vert.x, _vert.y, _depth.x, _depth.y);
    glViewport(0, 0, w, h);
}

void Scene::paintGL() // отрисовка сцены
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glRotatef(45, 0, 0, 1);

    glColor3f(1,0,0);
    glColor3f(1, 1, 1);
    _f.Draw();
}

float Scene::GetDt() // считает время с последнего своего вызова (первый раз со старта таймера)
{
    float time = (float)_timer->msecsTo(QTime::currentTime()) / 1000.f;
    float dt = time - _oldTime;
    _oldTime = time;
    return dt;
}

void Scene::UpdateStatistic(float dt) // выводит в заголовок количество фпс и количество частиц в обработке
{
    _fps++;
    _sec += dt;
    if (_sec >= 1)
    {
        //int pCount = _fw.ParticleCount();
        //setWindowTitle("fps = " + QString::number(_fps) + " | particles count = " + QString::number(pCount));
        _sec -= 1;
        _fps = 0;
    }
}

void Scene::Update()
{

    float dt = GetDt();

    _f.Update(dt);

    updateGL(); // отрисовка

    UpdateStatistic(dt);
}

void Scene::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   _mousePos = Field::ToCell(ScreenToWorld(pe->pos()), 0);
   setWindowTitle(QString::number(round(_mousePos.x)) + " " + QString::number(round(_mousePos.y)));
   _f.Click(round(_mousePos.x), round(_mousePos.y));
}

glm::vec2 Scene::ScreenToWorld(QPoint p) // переводит координаты окна в координаты сцены
{
    float x = ( (float)p.x() / (float)width() * (float)(abs(_hor.x) + abs(_hor.y)) - (float)abs(_hor.x));
    float y = (((float)height() - (float)p.y()) / (float)height() * (float)(abs(_vert.x) + abs(_vert.y)) - (float)abs(_vert.x) );
    return glm::vec2( x, y );
}

void Scene::DrawTile(glm::vec2 pos, GLuint texture)
{
    float size = 0.5f;
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex2fv(&glm::vec2(pos.x - size, pos.y - size)[0]);
        glTexCoord2f(0,1);
        glVertex2fv(&glm::vec2(pos.x - size, pos.y + size)[0]);
        glTexCoord2f(1,0);
        glVertex2fv(&glm::vec2(pos.x + size, pos.y - size)[0]);
        glTexCoord2f(1,1);
        glVertex2fv(&glm::vec2(pos.x + size, pos.y + size)[0]);
    glEnd();
}

void Scene::DrawBackGround(GLuint texture)
{

    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex2fv(&glm::vec2(_hor.x, _vert.x)[0]);
        glTexCoord2f(0,1);
        glVertex2fv(&glm::vec2(_hor.x, _vert.y)[0]);
        glTexCoord2f(1,0);
        glVertex2fv(&glm::vec2(_hor.y, _vert.x)[0]);
        glTexCoord2f(1,1);
        glVertex2fv(&glm::vec2(_hor.y, _vert.y)[0]);
    glEnd();
}

GLuint Scene::InitTexture(QString path)
{
    GLuint textureId(0);

    QImage pm(path);
    if (pm.isNull()) // проверка на загрузку текстуры
    {
        setWindowTitle("no image: " + path);
        //_isAllLoad = false;
        return 0;
    }
    pm = QGLWidget::convertToGLFormat(pm);

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)pm.width(), (GLsizei)pm.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pm.bits());

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureId;
}

void Scene::InitFireWork() // тут нахардкожено, вместо работы с фалом настроек
{

}

