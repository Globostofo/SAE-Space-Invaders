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
#include "file.h"
//#include "spaceinvaders.h"

using namespace std;
using namespace chrono;
using namespace nsGraphics;
using namespace nsGui;
using namespace nsConsts;
using namespace nsScene;
using namespace nsEntity;
using namespace nsBox;
using namespace nsFile;
//using namespace nsSpaceInvaders;

int main() {
    srand(time(NULL));

    // Initialise le système
    MinGL window("S102 - Space Invaders", WINSIZE, Vec2D(850, 80), KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // Settings provenant du yaml file
    map<string,string> settings;
    nsFile::readConfFile(settings);

    // Constantes qui tient le thème
    nsScene::Theme theme;
    switch (stoi(settings["Theme"])) {
        case 0 :{theme =BASE; break; }
        case 1 :{theme =SKY; break; }
        case 2 :{theme =SEA; break; }
        case 3 :{theme =WINDOWS; break; }
    }

    // Variable qui tient la scène à afficher
    SceneID currentScene = MAIN_MENU;

    // Instanciation et initialisations des scènes
    Sprite bg(nsConsts::bgMenu);
    Scene sceneMainMenu {bg};
    initMainMenu(sceneMainMenu);
    Scene sceneScoreMenu {bg};
    initScoreMenu(sceneScoreMenu);
    Scene sceneGame {Sprite(getBgPathByTheme(theme))};
    nsSpaceInvaders::Data gameData;
    Scene sceneGameOver {bg};
    initGameOverScene(sceneGameOver);
    vector<string> leaderboard; // passer en parametre que à init scene settings
    Scene sceneSettings {bg};
    initSettingsScene(sceneSettings,settings);

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen()) {

        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On appelle la fonction de la scène correspondante
        switch (currentScene) {

            case MAIN_MENU: {
                computeMainMenu(window, theme, sceneMainMenu, currentScene, sceneGame, gameData);
                break;
            }
            case SCORE_MENU: {
                computeScoreMenu(window, sceneScoreMenu, currentScene);
                break;
            }
            case SETTINGS_MENU: {
                computeSettingsMenu(window, sceneSettings, currentScene, settings);
                break;
            }
            case GAME: {
                computeGameScene(window, theme, sceneGame, currentScene, gameData, settings);
                break;
            }
            case GAME_OVER_MENU: {
                computeGameOverScene(window, theme, sceneGameOver, currentScene, gameData);
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
