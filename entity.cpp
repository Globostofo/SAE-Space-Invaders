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

namespace constantes {
    const int WinwodX= 800;
    const int WinwodY= 600;
    const string playerBulletSprite = "res/laser-windo.si2";
    const string playerSprite = "res/Windo.si2";

    const string enemyBulletSprite = "res/ls-aux.si2";
    const string invaderSprite = "res/linux.si2";
    const unsigned nbOfInvaders = 5;

    const unsigned reloadTime = 500;   // milliseconds
}

enum EntityTypes {
    SHIP,
    SHIP_BULLET,
    INVADER,
    INVADER_BULLET
};

struct Entity{
    EntityTypes type;
    nsGui::Sprite sprite; // nsGui::Sprite("",nsGraphics::Vec2D(0, 0));
    unsigned lifePoints;
    nsGraphics::Vec2D firstBound;
    nsGraphics::Vec2D secondBound;
    int speed = 10;
    nsGraphics::Vec2D velocity {0,0};
    bool canGoOutOfBounds = false;
};

bool isOutOfBounds(const Entity &entity) {
    nsGraphics::Vec2D spriteSize = entity.sprite.computeSize();
    vector<int> spriteXs {entity.sprite.getPosition().getX(),
                          entity.sprite.getPosition().getX() + spriteSize.getX()};
    vector<int> spriteYs {entity.sprite.getPosition().getY(),
                          entity.sprite.getPosition().getY() + spriteSize.getY()};

    // For each corner of sprite
    for (const int &xCorner : spriteXs) for (const int &yCorner : spriteYs)
        // If the corner is inside of bounds
        if (nsGraphics::Vec2D{xCorner,yCorner}.isColliding(entity.firstBound, entity.secondBound))
            // We consider the entity isn't out of binds
            return false;

    // If we are here, each corner is out of bounds
    // So entity is out of bounds
    return true;
}

void initInvadersList (const MinGL &window, vector<Entity> &invaders) {
    nsGui::Sprite invaderSprite {constantes::invaderSprite, {0,0}};
    nsGraphics::Vec2D spriteSize = invaderSprite.computeSize();
    for (unsigned i=0; i<constantes::nbOfInvaders; ++i) {
        invaders.push_back(Entity {INVADER,
                                   invaderSprite,
                                   3,
                                   nsGraphics::Vec2D {0,0},
                                   window.getWindowSize()-spriteSize,
                                   10*(int(i)+1)});
    }
}

void moveEntities(Entity &entity) {
    nsGraphics::Vec2D entityPos = entity.sprite.getPosition();

    if (!entity.canGoOutOfBounds) {
        nsGraphics::Vec2D deltaFirstBound  = entity.firstBound  - entityPos;
        nsGraphics::Vec2D deltaSecondBound = entity.secondBound - entityPos;
        entity.velocity.setX(clamp(entity.velocity.getX(),
                                   deltaFirstBound.getX(),
                                   deltaSecondBound.getX()));
        entity.velocity.setY(clamp(entity.velocity.getY(),
                                   deltaFirstBound.getY(),
                                   deltaSecondBound.getY()));
    }

    entity.sprite.setPosition(entity.sprite.getPosition() + entity.velocity);

}

void moveEntities(vector<Entity> &entityVec) {
    for (Entity &entity : entityVec)
        moveEntities(entity);
}

void playerMove(MinGL &window, Entity &entity) {

    // Get user inputs
    nsGraphics::Vec2D inputDirection {
        window.isPressed({'d', false}) - window.isPressed({'q', false}),
        window.isPressed({'s', false}) - window.isPressed({'z', false})
    };
    double inputMagn = inputDirection.computeMagnitude();

    // If size is 0, entity must not move
    if (inputMagn == 0) {
        entity.velocity = {0,0};
        return;
    }

    // Normalize, speed up and round the inputDirection vector
    entity.velocity = {
        round(inputDirection.getX() / inputMagn * entity.speed),
        round(inputDirection.getY() / inputMagn * entity.speed)
    };

    // Now we can move entity :)
    moveEntities(entity);
}

void playerShoot(MinGL &window, Entity &entity, vector<Entity> &bullets, bool &canShoot, chrono::steady_clock::time_point &lastShot) {

    if(canShoot) {
        if (window.isPressed({' ',false})) {
            canShoot = false;
            lastShot = chrono::steady_clock::now();
            bullets.push_back(Entity {
                                  SHIP_BULLET,
                                  nsGui::Sprite (constantes::playerBulletSprite, entity.sprite.getPosition()),
                                  1,
                                  nsGraphics::Vec2D (0,0),
                                  window.getWindowSize(),
                                  15,
                                  nsGraphics::Vec2D (0,-10),
                                  true
                              });
        }
    }

    else if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - lastShot).count() >= constantes::reloadTime)
        canShoot = true;
}



void dispEntities(MinGL &window, const Entity &entity) {
    window << entity.sprite;
}

void dispEntities(MinGL &window, const vector<Entity> &entityVec) {
    for (const Entity &entity : entityVec)
        dispEntities(window, entity);
}

int main() {
    // Initialise le système
    MinGL window("Jeu", nsGraphics::Vec2D(constantes::WinwodX, constantes::WinwodY), nsGraphics::Vec2D(50, 50), nsGraphics::KGray);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // Player initialization
    nsGui::Sprite pSprite {constantes::playerSprite, nsGraphics::Vec2D{0,0}};
    nsGraphics::Vec2D spriteSize = pSprite.computeSize();
    Entity player {SHIP,
                   pSprite,
                   3,
                   nsGraphics::Vec2D {10, window.getWindowSize().getY()-spriteSize.getY()-10},
                   window.getWindowSize() - spriteSize - nsGraphics::Vec2D {10,10}};
    vector<Entity> playerBullets;

    // Invaders initialization
    vector<Entity> invaders;
    initInvadersList(window, invaders);
    vector<Entity> invadersBullets;

    //Init shooting variables for delay
    bool canShoot = true;
    chrono::steady_clock::time_point lastShot;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen()) {

        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // Move entities
        playerMove(window, player);
        //moveInvaders(invaders);
        moveEntities(playerBullets);
        moveEntities(invadersBullets);

        // Shoots
        playerShoot(window, player, playerBullets, canShoot, lastShot);
        //invadersShoots

        // Check collisions
        //entitiesCollisions(player, invadersBullets);
        //entitiesCollisions(invaders, playerBullets);
        //entitiesCollisions(playerBullets, invadersBullets);

        // Delete all entities where lives=0
        // deleteEntitiesIfDies(player);
        // deleteEntitiesIfDies(invaders);
        // deleteEntitiesIfDies(playersBullets);
        // deleteEntitiesIfDies(invadersBullets);

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
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - frameTime);

    }
    return 0;
}
