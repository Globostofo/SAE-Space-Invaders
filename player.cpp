/*!
 * @author
 * @brief
 * oxygen commentary
***/

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
    const string playerBulletSprite = "res/windowsBullet.si2";
    const string playerSprite = "res/windows.si2";

    const string enemyBulletSprite = "res/windowsBullet.si2";
    const string invaderSprite = "res/linux.si2";
    const unsigned nbOfInvaders = 5;

    const int playerBulletDirection = -10;
    const int enemyBulletDirection = 10;
    const int speed = 10;
}

struct entityInfos{
    nsGui::Sprite entity; // nsGui::Sprite("",nsGraphics::Vec2D(0, 0));
    unsigned lifePoints;
    nsGui::Sprite entityBullet;// nsGui::Sprite("",nsGraphics::Vec2D(0, 0));
    vector<nsGui::Sprite> bullets;
};

void showEntity(MinGL &window, entityInfos Entity)
{
    window << Entity.entity;
}

void showBullet(MinGL &window, entityInfos &Entity, int direction){
    for(unsigned i = 0; i<Entity.bullets.size(); ++i){
        window<<Entity.bullets[i];
        Entity.bullets[i].setPosition(nsGraphics::Vec2D(Entity.bullets[i].getPosition().getX(),Entity.bullets[i].getPosition().getY()+direction));
    }
}

void getShot(MinGL &window, entityInfos &Entity, bool &canShoot, bool &startTimer){
    if(window.isPressed({' ',false}) && canShoot){
        canShoot = false;
        startTimer = true;
        nsGui::Sprite bulletToAdd =Entity.entityBullet;
        bulletToAdd.setPosition(nsGraphics::Vec2D(Entity.entity.getPosition().getX()+Entity.entity.computeSize().getX()/2-Entity.entityBullet.computeSize().getX()/2, Entity.entity.getPosition().getY()));
        Entity.bullets.push_back(bulletToAdd);
    }
}

void hasBeenShot(entityInfos &EntityShooting,entityInfos &Target){
        nsShape::Rectangle entityShotHitBox(Target.entity.getPosition(),Target.entity.computeSize(), nsGraphics::KBlue);//color inutile
        for(auto iter = EntityShooting.bullets.begin(); iter !=EntityShooting.bullets.end(); ){
            nsGraphics::Vec2D bullet((*iter).getPosition().getX(),(*iter).getPosition().getY());
            if(bullet.isColliding(entityShotHitBox.getFirstPosition(),entityShotHitBox.getSecondPosition())){
                EntityShooting.bullets.erase(iter);
                cout<<"la balle a touche"<<endl;
                Target.lifePoints-=1; //faire fonct hasBeenKilled
            }
            else{
                ++iter;
            }
        }
}

void getPlayerMoves(MinGL &window,entityInfos &Entity)
{

    // On vérifie si ZQSD est pressé, et met a jour la position
        if (window.isPressed({'z', false}))
            if(Entity.entity.getPosition().getY()>0 && Entity.entity.getPosition().getY()-constantes::speed<constantes::WinwodY)
                 Entity.entity.setPosition(nsGraphics::Vec2D( Entity.entity.getPosition().getX(),Entity.entity.getPosition().getY() - constantes::speed));
        if (window.isPressed({'s', false}))
            if(Entity.entity.getPosition().getY()>=0 && (Entity.entity.getPosition().getY()+constantes::speed+Entity.entity.computeSize().getY())<=constantes::WinwodY)
                Entity.entity.setPosition(nsGraphics::Vec2D( Entity.entity.getPosition().getX(),Entity.entity.getPosition().getY() + constantes::speed));
        if (window.isPressed({'q', false}))
            if(Entity.entity.getPosition().getX()>0 && Entity.entity.getPosition().getX()-constantes::speed<constantes::WinwodX)
                Entity.entity.setPosition(nsGraphics::Vec2D( Entity.entity.getPosition().getX()-constantes::speed,Entity.entity.getPosition().getY()));
        if (window.isPressed({'d', false}))
            if(Entity.entity.getPosition().getX()>=0 && (Entity.entity.getPosition().getX()+constantes::speed+Entity.entity.computeSize().getX())<constantes::WinwodX)
                Entity.entity.setPosition(nsGraphics::Vec2D( Entity.entity.getPosition().getX()+constantes::speed,Entity.entity.getPosition().getY()));
}

void initInvadersList (vector<entityInfos> &invaders){
    for(unsigned i =0; i<constantes::nbOfInvaders ; ++i){
        invaders.push_back({nsGui::Sprite(constantes::invaderSprite,nsGraphics::Vec2D(0, 0)),
                3,
                nsGui::Sprite(constantes::enemyBulletSprite,nsGraphics::Vec2D(0, 0)),
                vector<nsGui::Sprite>{}});
    }
}

int main()
{
    // Initialise le système
    MinGL window("Jeu", nsGraphics::Vec2D(constantes::WinwodX, constantes::WinwodY), nsGraphics::Vec2D(50, 50), nsGraphics::KGray);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // Init Player
    entityInfos player{nsGui::Sprite(constantes::playerSprite,nsGraphics::Vec2D(500, 500)),
                      3,
                      nsGui::Sprite(constantes::playerBulletSprite,nsGraphics::Vec2D(0, 0)),
                vector<nsGui::Sprite>{}};
    //Init Invader list
    vector<entityInfos> invaders;
    initInvadersList(invaders);

    //Init shooting variables for delay
    bool canShoot = true;
    chrono::steady_clock::time_point startShoot = chrono::steady_clock::now();
    chrono::steady_clock::time_point lastShot;
    bool startTimer = false;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();
        // On fait tourner les procédures
        if(startTimer){
            lastShot = chrono::steady_clock::now();
            if(chrono::duration_cast<chrono::milliseconds> (lastShot - startShoot).count() > 500){
                startShoot = chrono::steady_clock::now();
                canShoot=true;
            }
        }
        getShot(window,player, canShoot,startTimer);
        getPlayerMoves(window,player);

        showEntity(window,player);
        showBullet(window,player,constantes::playerBulletDirection);
        //hasBeenShot(player,enemy); if player shoots and target = enemy -> loop to check every enemy element in the struct


        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
}

