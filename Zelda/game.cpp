#include "game.h"
#include "view.h"
#include <QApplication>
#include <QDesktopWidget>
#include "slime.h"

Game::Game(View *view)
{
    this->view = view;
    this->scene = view->scene();
    QRect resolution = QApplication::desktop()->screenGeometry();
    this->WIDTH = resolution.width();
    this->HEIGHT = resolution.height();
}

void Game::load(){
    resource = new Resource();
    resource->load();

    camera = new Camera(this);

    world = new World(this);
    world->load();
    scene->addItem(world);

    loadEntities();

    gui = new Gui(this);
    scene->addItem(gui);
}

void Game::loadEntities(){
    world->addEntity(new Slime(this, 30, 30));
}

void Game::update(){
    STEPS++;
    world->update();
}