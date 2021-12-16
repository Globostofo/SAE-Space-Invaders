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
    const int speed = 10;
    const string bulletSprite = "res/windowsBullet.si2";
    const string playerSprite = "res/windows.si2";
}

struct elements{
    nsGui::Sprite bullet = nsGui::Sprite(constantes::bulletSprite,nsGraphics::Vec2D(0, 0));
    vector<nsGui::Sprite> projectiles;
    nsGui::Sprite player = nsGui::Sprite(constantes::playerSprite,nsGraphics::Vec2D(20, 20));
    unsigned lives = 3;
};

void hasBeenShot(MinGL &window , elements &listeProjects){
    nsShape::Rectangle rect1(nsGraphics::Vec2D(20, 20), nsGraphics::Vec2D(50, 50), nsGraphics::KBlue);
    window << rect1;
        for(auto iter = listeProjects.projectiles.begin(); iter !=listeProjects.projectiles.end(); ){
            nsGraphics::Vec2D bullet((*iter).getPosition().getX(),(*iter).getPosition().getY());
            if(bullet.isColliding(rect1.getFirstPosition(),rect1.getSecondPosition())){
                listeProjects.projectiles.erase(iter);
                cout<<"la balle a touche"<<endl;
            }
            else{
                ++iter;
            }
        }
}

void dessinerPersos(MinGL &window, elements listeProjects)
{
    // On dessine le player
    window << listeProjects.player;
}


//void placerProjectile(MinGL &window, elements &listeProjects){
//    for(auto iter = listeProjects.projectiles.begin(); iter !=listeProjects.projectiles.end(); ){
//        if((*iter).getPosition().getX() < 0){
//            listeProjects.projectiles.erase(iter);
//        }
//        else{
//            ++iter;
//        }
//        window<<listeProjects.projectiles[0];//debug
//        cout<<listeProjects.projectiles.size()<<endl;//debug
//        cout<<(*iter).getPosition();//debug
//        window << (*iter);
//        (*iter).setPosition(nsGraphics::Vec2D((*iter).getPosition().getX() ,(*iter).getPosition().getY()-10));
//    }
//}//placerProjectile en utilisant iterator
void placerProjectile(MinGL &window, elements &listeProjects){
    for(unsigned i = 0; i<listeProjects.projectiles.size(); ++i){
        window<<listeProjects.projectiles[i];
        listeProjects.projectiles[i].setPosition(nsGraphics::Vec2D(listeProjects.projectiles[i].getPosition().getX(),listeProjects.projectiles[i].getPosition().getY()-10));
    }
}
void getShot(MinGL &window, elements &listeProjects, bool &canShoot, bool &startTimer){
    if(window.isPressed({' ',false}) && canShoot){
        canShoot = false;
        startTimer = true;
        nsGui::Sprite bulletToAdd =listeProjects.bullet;
        bulletToAdd.setPosition(nsGraphics::Vec2D(listeProjects.player.getPosition().getX()+listeProjects.player.computeSize().getX()/2-listeProjects.bullet.computeSize().getX()/2, listeProjects.player.getPosition().getY()));
        listeProjects.projectiles.push_back(bulletToAdd);
    }
}
void clavier(MinGL &window,elements &listeProjects)
{

    // On vérifie si ZQSD est pressé, et met a jour la position
        if (window.isPressed({'z', false}))
            if(listeProjects.player.getPosition().getY()>0 && listeProjects.player.getPosition().getY()-constantes::speed<constantes::WinwodY)
                 listeProjects.player.setPosition(nsGraphics::Vec2D( listeProjects.player.getPosition().getX(),listeProjects.player.getPosition().getY() - constantes::speed));
        if (window.isPressed({'s', false}))
            if(listeProjects.player.getPosition().getY()>=0 && (listeProjects.player.getPosition().getY()+constantes::speed+listeProjects.player.computeSize().getY())<=constantes::WinwodY)
                listeProjects.player.setPosition(nsGraphics::Vec2D( listeProjects.player.getPosition().getX(),listeProjects.player.getPosition().getY() + constantes::speed));
        if (window.isPressed({'q', false}))
            if(listeProjects.player.getPosition().getX()>0 && listeProjects.player.getPosition().getX()-constantes::speed<constantes::WinwodX)
                listeProjects.player.setPosition(nsGraphics::Vec2D( listeProjects.player.getPosition().getX()-constantes::speed,listeProjects.player.getPosition().getY()));
        if (window.isPressed({'d', false}))
            if(listeProjects.player.getPosition().getX()>=0 && (listeProjects.player.getPosition().getX()+constantes::speed+listeProjects.player.computeSize().getX())<constantes::WinwodX)
                listeProjects.player.setPosition(nsGraphics::Vec2D( listeProjects.player.getPosition().getX()+constantes::speed,listeProjects.player.getPosition().getY()));
}

int main()
{
    // Initialise le système
    MinGL window("Jeu", nsGraphics::Vec2D(constantes::WinwodX, constantes::WinwodY), nsGraphics::Vec2D(50, 50), nsGraphics::KGray);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // Variable qui contient les pojectiles, du temps entre les tirs
    elements listeProjects;
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
        getShot(window,listeProjects, canShoot,startTimer);
        clavier(window,listeProjects);

        dessinerPersos(window,listeProjects);
        placerProjectile(window,listeProjects);
        hasBeenShot(window, listeProjects);

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
