#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/gui/sprite.h"

using namespace std;

namespace constantes {
    const int WinwodX= 1500;
    const int WinwodY= 800;
    const string playerBulletSprite = "a";
    const string playerSprite = "res/Windo.si2";

    const string enemyBulletSprite = "res/ls-aux.si2";
    const string invaderSprite = "res/linux.si2";
    const int nbOfInvaders = 5;

    const int playerBulletDirection = -10;
    const int enemyBulletDirection = 10;
}

struct entityInfos{
    nsGui::Sprite entity; // nsGui::Sprite("",nsGraphics::Vec2D(0, 0));
    unsigned lifePoints;
    nsGui::Sprite entityBullet;// nsGui::Sprite("",nsGraphics::Vec2D(0, 0));
    vector<nsGui::Sprite> bullets;
};

void showEntity(MinGL &window, entityInfos Entity);

void showBullet(MinGL &window, entityInfos &Entity, int direction);

void getShot(MinGL &window, entityInfos &Entity, bool &canShoot, bool &startTimer);

void hasBeenShot(MinGL &window , entityInfos &Entity);

void initInvadersList (vector<entityInfos> &invaders);

int main();
