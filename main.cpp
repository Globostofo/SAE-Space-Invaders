#define FPS_LIMIT 60

#include <iostream>
#include <cmath>
#include <thread>

#include "mingl/mingl.h"
#include "mingl/graphics/vec2d.h"
#include "mingl/gui/sprite.h"

#include "consts.h"
#include "scene.h"
#include "box.h"
//#include "spaceinvaders.h"

using namespace std;
using namespace chrono;
using namespace nsGraphics;
using namespace nsGui;
using namespace nsConsts;
using namespace nsScene;
using namespace nsEntity;
using namespace nsBox;
//using namespace nsSpaceInvaders;

// This main is to test entities
/*int main() {
    srand(time(NULL));

    // Initialise le système
    MinGL window("Jeu",
                 WINSIZE,
                 Vec2D(50,50),
                 KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    microseconds frameTime = microseconds::zero();

    // Player initialization
    Sprite pSprite(playerSprite1, Vec2D());
    Vec2D spriteSize = pSprite.computeSize();
    Entity player {
        SHIP,
        pSprite,
        spriteSize,
        3,
        Box {Vec2D(10, window.getWindowSize().getY()-spriteSize.getY()-100),
                    window.getWindowSize() - spriteSize - Vec2D(10,10)},
    };
    vector<Entity> playerBullets;
    vector<Entity> shields;
    initShieldsList(window, shields);
    bool canShoot = true;
    steady_clock::time_point lastShot;

    // Invaders initialization
    vector<Entity> invaders;
    initInvadersList(window, invaders);
    vector<Entity> invadersBullets;
    bool invadersCanShoot = false;
    steady_clock::time_point invadersLastShot = steady_clock::now();
    unsigned invadersLine = 0;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen()) {

        // Récupère l'heure actuelle
        time_point<steady_clock> start = steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // Move entities
        playerMove(window, player);
        invadersMove(invaders, invadersLine);
        moveEntities(playerBullets);
        moveEntities(invadersBullets);

        // Shoots
        playerShoot(window, player, playerBullets, canShoot, lastShot);
        invadersShoot(window, invaders, invadersBullets, invadersCanShoot, invadersLastShot);

        // Check collisions
        entitiesCollisions(player, invadersBullets);
        entitiesCollisions(invaders, playerBullets);
        entitiesCollisions(playerBullets, invadersBullets);
        entitiesCollisions(shields, playerBullets);
        entitiesCollisions(shields, invaders);
        entitiesCollisions(shields, invadersBullets);

        // Delete all entities where lives=0
        deleteDiedEntities(invaders);
        deleteDiedEntities(playerBullets);
        deleteDiedEntities(invadersBullets);
        deleteDiedEntities(shields);

        // Display all entities
        dispEntities(window, playerBullets);
        dispEntities(window, invadersBullets);
        dispEntities(window, player);
        dispEntities(window, invaders);
        dispEntities(window, shields);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On récupère le temps de frame
        frameTime = duration_cast<microseconds>(steady_clock::now() - start);

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(milliseconds(1000 / FPS_LIMIT) - frameTime);

        // End game
        if (player.lifePoints <= 0) {
            window.stopGraphic();
            cout << "YOU LOSE NOOB" << endl;
        }
        else if (!invaders.size()) {
            window.stopGraphic();
            cout << "YOU WIN NOOB" << endl;
        }

    }

    return 0;
}*/

int main() {

    // Initialise le système
    MinGL window("S102 - Space Invaders", WINSIZE, Vec2D(850, 80), KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // Constantes qui tient le thème
    const nsScene::Theme theme = nsScene::SKY;

    // Variable qui tient la scène à afficher
    SceneID currentScene = MAIN_MENU;

    // Instanciation et initialisations des scènes
    Sprite bg(getBgPathByTheme(theme));
    Scene sceneMainMenu {bg};
    initMainMenu(sceneMainMenu);
    Scene sceneSettingsMenu {bg};
    initSettingsMenu(sceneSettingsMenu);
    Scene sceneScoreMenu {bg};
    initScoreMenu(sceneScoreMenu);
    Scene sceneGame {bg};
    nsSpaceInvaders::Data gameData;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen()) {

        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On appelle la fonction de la scène correspondante
        switch (currentScene) {

            case MAIN_MENU: {
                computeScene(window, theme, sceneMainMenu, currentScene, sceneGame, gameData);
                break;
            }

            case SETTINGS_MENU: {
                computeScene(window, theme, sceneSettingsMenu, currentScene, sceneGame, gameData);
                break;
            }

            case SCORE_MENU: {
                computeScene(window, theme, sceneScoreMenu, currentScene, sceneGame, gameData);
                break;
            }

            case GAME: {
                computeScene(window, theme, sceneGame, currentScene, sceneGame, gameData);
                break;
            }

        }

        // On vide le buffer
        window.getEventManager().clearEvents();

        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

    }

    return 0;
}
