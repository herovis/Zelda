#include "view.h"
#include <QOpenGLWidget>
#include <QApplication>
#include "player.h"
#include <QDebug>

View::View(QGraphicsScene *scene)
{
    setScene(scene);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setViewport(new QOpenGLWidget(this));
    setMouseTracking(true);

    game = new Game(this);
    game->load();

    timerUpdate = new QTimer(this);
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));
    timerUpdate->start(16);
}

void View::update()
{
    game->update();
    game->camera->update(game->player);

    this->scene()->update(QRectF(0, 0, game->WIDTH, game->HEIGHT));
}

void View::mousePressEvent(QMouseEvent *event)
{

}

void View::mouseReleaseEvent(QMouseEvent *event)
{

}

void View::mouseMoveEvent(QMouseEvent *event){

}

void View::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) exit(0);
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A) game->player->setDX(-1);
    if(event->key() == Qt::Key_Right|| event->key() == Qt::Key_D) game->player->setDX(1);
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W) game->player->setDY(-1);
    if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S) game->player->setDY(1);
    if(event->key() == Qt::Key_Space && game->player->swing == 0) game->player->attack();
    if(event->key()== Qt::Key_Shift) game->player->speed=3;
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Left || event->key() == Qt::Key_A) && game->player->dx == -1) game->player->setDX(0);
    if((event->key() == Qt::Key_Right || event->key() == Qt::Key_D) && game->player->dx == 1) game->player->setDX(0);
    if((event->key() == Qt::Key_Up || event->key() == Qt::Key_W) && game->player->dy == -1) game->player->setDY(0);
    if((event->key() == Qt::Key_Down || event->key() == Qt::Key_S) && game->player->dy == 1) game->player->setDY(0);
    if(event->key()== Qt::Key_Shift)game->player->speed=2;

}
