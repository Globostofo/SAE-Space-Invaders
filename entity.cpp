/*!
 * @author
 * @brief
 * oxygen commentary
***/

#define FPS_LIMIT 60

#include <iostream>
#include <cmath>        // sqrt, round
#include <algorithm>    // clamp
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/gui/sprite.h"

using namespace std;
using namespace chrono;
using namespace nsGraphics;
using namespace nsGui;

namespace constantes {

const int WinwodX= 800;
const int WinwodY= 600;
const string playerBulletSprite = "res/laser-windo.si2";
const string playerSprite = "res/Windo.si2";

const string enemyBulletSprite = "res/ls-aux.si2";
const string invaderSprite = "res/linux.si2";
const unsigned nbOfInvaders = 5;

const unsigned reloadTime = 500;   // milliseconds

} // namespace constantes

namespace box {

struct Box {
    Vec2D firstPosition;
    Vec2D secondPosition;
};

bool areColliding(const Vec2D &position, const Box &box) {
    return box.firstPosition.getX() <= position.getX() <= box.secondPosition.getX()
            && box.firstPosition.getY() <= position.getX() <= box.secondPosition.getY();
}

bool areColliding(const Box &box1, const Box &box2) {
    Vec2D b1c1 = box1.firstPosition;
    Vec2D b1c2 = box1.secondPosition;
    Vec2D b2c1 = box2.firstPosition;
    Vec2D b2c2 = box2.secondPosition;

    return !(b1c2.getX() < b2c1.getX() || b2c2.getX() < b1c1.getX()
             || b1c2.getY() < b2c1.getY() || b2c2.getY() < b1c1.getY());
}

void clampInBox(Vec2D &position, const Box &box) {
    position.setX(clamp(position.getX(),
                        box.firstPosition.getX(),
                        box.secondPosition.getY()));
    position.setY(clamp(position.getY(),
                        box.firstPosition.getY(),
                        box.secondPosition.getY()));
}

} // namespace box

namespace entity {

enum EntityType {
    SHIP,
    SHIP_BULLET,
    INVADER,
    INVADER_BULLET
};

const map<EntityType, vector<EntityType>> entitiesCollider {
    {SHIP,           {INVADER, INVADER_BULLET}},
    {SHIP_BULLET,    {INVADER, INVADER_BULLET}},
    {INVADER,        {SHIP_BULLET}},
    {INVADER_BULLET, {SHIP, SHIP_BULLET}}
};

struct Entity{
    EntityType type;
    Sprite sprite;
    Vec2D spriteSize;
    int lifePoints;
    box::Box bounds;
    int speed = 10;
    Vec2D direction = Vec2D();
    bool canGoOutOfBounds = false;
};

box::Box getEntityBox(const Entity &entity) {
    Vec2D spritePos = entity.sprite.getPosition();
    return box::Box {spritePos, spritePos+entity.spriteSize};
}

void dispEntities(MinGL &window, const Entity &entity) {
    window << entity.sprite;
}

void dispEntities(MinGL &window, const vector<Entity> &entityVec) {
    for (const Entity &entity : entityVec)
        dispEntities(window, entity);
}

bool isOutOfBounds(const Entity &entity) {
    return entity.canGoOutOfBounds && !box::areColliding(entity.bounds, getEntityBox(entity));
}

void moveEntities(Entity &entity) {
    Vec2D newPos = entity.sprite.getPosition() + entity.direction.toSize(entity.speed);
    if (!entity.canGoOutOfBounds)
        box::clampInBox(newPos, entity.bounds);
    entity.sprite.setPosition(newPos);
}

void moveEntities(vector<Entity> &entityVec) {
    for (Entity &entity : entityVec)
        moveEntities(entity);
}

void entitiesCollisions(Entity &entity1, Entity &entity2) {
    if (box::areColliding(getEntityBox(entity1), getEntityBox(entity2))) {
        const vector<EntityType> whoHurts1 = entitiesCollider.find(entity1.type)->second;
        const vector<EntityType> whoHurts2 = entitiesCollider.find(entity2.type)->second;
        if (find(whoHurts1.begin(), whoHurts1.end(), entity2.type) != whoHurts1.end()) {
            entity1.lifePoints -= 1;
        }
        if (find(whoHurts2.begin(), whoHurts2.end(), entity1.type) != whoHurts2.end()) {
            entity2.lifePoints -= 1;
        }
    }
}

void entitiesCollisions(Entity &entity1, vector<Entity> &entityVec2) {
    for (Entity &entity2: entityVec2)
        entitiesCollisions(entity1, entity2);
}

void entitiesCollisions(vector<Entity> &entityVec1,
                        vector<Entity> &entityVec2) {
    for (Entity &entity1 : entityVec1) for (Entity &entity2 : entityVec2)
        entitiesCollisions(entity1, entity2);
}

void deleteDiedEntities(vector<Entity> &entities) {
    for (vector<Entity>::iterator it=entities.begin(); it<entities.end(); ++it)
        if ((*it).lifePoints <= 0 || ((*it).canGoOutOfBounds && isOutOfBounds(*it))){
            entities.erase(it);
        }
}

} // namespace entity

void initInvadersList (const MinGL &window, vector<entity::Entity> &invaders) {
    Vec2D spriteSize = Sprite(constantes::invaderSprite).computeSize();
    for (unsigned i=0; i<constantes::nbOfInvaders; ++i) {
        Sprite invaderSprite (constantes::invaderSprite, Vec2D(100*i));
        invaders.push_back(
                    entity::Entity {
                        entity::INVADER,
                        invaderSprite,
                        spriteSize,
                        3,
                        box::Box{Vec2D(),
                                 window.getWindowSize()-spriteSize},
                        5,
                        Vec2D(1,0)
                    }
                    );
    }
}

void playerMove(MinGL &window, entity::Entity &player) {
    player.direction.setX(window.isPressed({'d', false}) - window.isPressed({'q', false}));
    player.direction.setY(window.isPressed({'s', false}) - window.isPressed({'z', false}));
    moveEntities(player);
}

void invadersMove(MinGL &window, vector<entity::Entity> &invaders) {

    moveEntities(invaders);
}

void playerShoot(MinGL &window, entity::Entity &player,
                 vector<entity::Entity> &bullets,
                 bool &canShoot,
                 steady_clock::time_point &lastShot) {

    if(canShoot && window.isPressed({' ',false})) {
        canShoot = false;
        lastShot = steady_clock::now();
        Sprite bulletSprite (constantes::playerBulletSprite, player.sprite.getPosition());
        bullets.push_back(
                    entity::Entity {
                        entity::SHIP_BULLET,
                        bulletSprite,
                        bulletSprite.computeSize(),
                        1,
                        box::Box {Vec2D(0,0),
                                  window.getWindowSize()},
                        15,
                        Vec2D(0,-10),
                        true
                    }
                    );
    }

    else if (duration_cast<milliseconds>(steady_clock::now() - lastShot).count() >= constantes::reloadTime)
        canShoot = true;
}

int main() {
    // Initialise le système
    MinGL window("Jeu",
                 Vec2D(constantes::WinwodX, constantes::WinwodY),
                 Vec2D(50,50),
                 KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    microseconds frameTime = microseconds::zero();

    // Player initialization
    Sprite pSprite(constantes::playerSprite, Vec2D());
    Vec2D spriteSize = pSprite.computeSize();
    entity::Entity player {
        entity::SHIP,
                pSprite,
                spriteSize,
                3,
                box::Box {Vec2D(10, window.getWindowSize().getY()-spriteSize.getY()-10),
                          window.getWindowSize() - Vec2D(10,10)},
    };
    vector<entity::Entity> playerBullets;

    // Invaders initialization
    vector<entity::Entity> invaders;
    initInvadersList(window, invaders);
    vector<entity::Entity> invadersBullets;

    // Init shooting variables for delay
    bool canShoot = true;
    steady_clock::time_point lastShot;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen()) {

        // Récupère l'heure actuelle
        time_point<steady_clock> start = steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // Move entities
        playerMove(window, player);
        invadersMove(window, invaders);
        moveEntities(playerBullets);
        moveEntities(invadersBullets);

        // Shoots
        playerShoot(window, player, playerBullets, canShoot, lastShot);
        //invadersShoots

        // Check collisions
        entitiesCollisions(player, invadersBullets);
        entitiesCollisions(invaders, playerBullets);
        entitiesCollisions(playerBullets, invadersBullets);

        // Delete all entities where lives=0
        deleteDiedEntities(invaders);
        deleteDiedEntities(playerBullets);
        deleteDiedEntities(invadersBullets);

        // Display all entities
        dispEntities(window, playerBullets);
        dispEntities(window, invadersBullets);
        dispEntities(window, player);
        dispEntities(window, invaders);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On récupère le temps de frame
        frameTime = duration_cast<microseconds>(steady_clock::now() - start);

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(milliseconds(1000 / FPS_LIMIT) - frameTime);

    }

    return 0;
}
