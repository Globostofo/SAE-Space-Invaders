/*!
 *
 * @file    main.cpp
 * @author  Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
 * @date    January 2022
 * @brief
 *
 **/

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

using namespace std;
using namespace chrono;
using namespace nsGraphics;
using namespace nsGui;
using namespace nsConsts;
using namespace nsScene;
using namespace nsEntity;
using namespace nsBox;
using namespace nsFile;

int main() {
    srand(time(NULL));

    // Initialize the system
    MinGL window("S102 - Space Invaders", WINSIZE, Vec2D(850, 80), KBlack);
    window.initGlut();
    window.initGraphic();

    // Get the time of the frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // Settings from the config.yaml file
    map<string,string> settings;
    nsFile::readConfFile(settings);

    // Consts of the current game theme
    nsScene::Theme theme;
    switch (stoi(settings["Theme"])) {
        case 0 :{theme =BASE; break; }
        case 1 :{theme =SKY; break; }
        case 2 :{theme =SEA; break; }
        case 3 :{theme =WINDOWS; break; }
    }

    // Variable that stocks the current scene we are in
    SceneID currentScene = MAIN_MENU;

    // Initialization of the scenes
    Sprite bg(nsConsts::bgMenu);

    Scene sceneMainMenu {bg};
    initMainMenu(sceneMainMenu);

    Scene sceneScoreMenu {bg};
    initScoreMenu(sceneScoreMenu);

    Scene sceneGame {Sprite(getBgPathByTheme(theme))};
    nsSpaceInvaders::Data gameData;

    Scene sceneGameOver {bg};
    initGameOverScene(sceneGameOver);

    vector<string> leaderboard;

    Scene sceneSettings {bg};
    initSettingsScene(sceneSettings,settings);

    // Main loop
    while (window.isOpen()) {

        // Get current time
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // Clear the screen
        window.clearScreen();

        // We call the function corresponding to the current scene
        switch (currentScene) {

            case MAIN_MENU: {
                computeMainMenu(window, theme, sceneMainMenu, currentScene, sceneGame,sceneScoreMenu, gameData);
                break;
            }
            case SCORE_MENU: {
                computeScoreMenu(window, sceneScoreMenu, currentScene);
                break;
            }
            case SETTINGS_MENU: {
                computeSettingsMenu(window,theme, sceneSettings, currentScene, settings);
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

        // Empty the buffer
        window.getEventManager().clearEvents();

        // Finish current frame
        window.finishFrame();

        // We wait because i dont want to fry eggs on my CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // Get the frame time
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

    }

    return 0;
}// main
