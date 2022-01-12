#ifndef SCENE_H
#define SCENE_H

#include "mingl/mingl.h"
#include "mingl/graphics/rgbacolor.h"

#include "button.h"
#include "spaceinvaders.h"

namespace nsScene {

enum Theme {
    BASE,
    SKY,
    SEA,
    WINDOWS
};

enum SceneID {
    MAIN_MENU,
    SCORE_MENU,
    SETTINGS_MENU,
    GAME,
    GAME_OVER_MENU
};

struct Scene {
    nsGui::Sprite background;
    std::vector<nsButton::Button> buttons;      // store all buttons for a scene
    std::vector<nsEntity::Entity> entities;     // store all entities (empty for a menu)
    std::vector<nsGui::Text> texts;             // store all texts (usefull to settings and to display player lives remaining
}; // struct Scene

std::string getBgPathByTheme(const Theme &theme);

std::string getPlayerSpritePathByTheme(const Theme &theme);

std::string getInvaderSpritePathByTheme(const Theme &theme);

std::string getPlayerBulletSpritePathByTheme(const Theme &theme);

std::string getInvaderBulletSpritePathByTheme(const Theme &theme);

std::string getShieldSpritePathByTheme(const Theme &theme);

nsGraphics::RGBAcolor getTextColorByTheme(const Theme &theme);

std::string getPressedChars(MinGL &window,const bool isReset);

void initMainMenu(Scene &scene);

void initScoreMenu(Scene &scene);

void initSettingsScene(Scene &scene,std::map<std::string,std::string> &settings);

void initGameScene(Scene &scene, nsSpaceInvaders::Data &gameData, const Theme &theme);

void initGameOverScene(Scene &scene);

void displayScene(MinGL &window, const Scene &scene);

void computeMainMenu(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, Scene &gameScene, nsSpaceInvaders::Data &gameData);

void computeScoreMenu(MinGL &window, Scene &scene, SceneID &currentScene);

void computeSettingsMenu(MinGL &window, Scene &scene, SceneID &currentScene, std::map<std::string,std::string> settings);

void computeGameScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, nsSpaceInvaders::Data &gameData, std::map<std::string,std::string> settings);

void computeGameOverScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, nsSpaceInvaders::Data &gameData);

}

#endif // SCENE_H
