/*!
 *
 * @file    scene.h
 * @author  Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
 * @date    January 2022
 * @brief   Scene Management
 *
 **/

#ifndef SCENE_H
#define SCENE_H

#include "mingl/mingl.h"
#include "mingl/graphics/rgbacolor.h"

#include "button.h"
#include "spaceinvaders.h"

namespace nsScene {

/*!
  * @brief enum containing the differents scenes
  * @enum Theme : every theme is associated to a id
**/
enum Theme {
    BASE,
    SKY,
    SEA,
    WINDOWS
};// Theme

/*!
  * @brief enum containing the differents scenes ids
  * @enum every scene associated to a id
**/
enum SceneID {
    MAIN_MENU,
    SCORE_MENU,
    SETTINGS_MENU,
    GAME,
    GAME_OVER_MENU
};// SceneID

/*!
  * @brief struct used to store the elements in a scene
  * @struct every scene it's parameters
**/
struct Scene {
    nsGui::Sprite background;
    std::vector<nsButton::Button> buttons;      // store all buttons for a scene
    std::vector<nsEntity::Entity> entities;     // store all entities (empty for a menu)
    std::vector<nsGui::Text> texts;             // store all texts (usefull to settings and to display player lives remaining
}; // Scene

/*!
  * @brief function used to return the path of the Background depending on the theme
  * @param [in] theme: theme id
  * @fn string getBgPathByTheme(const Theme &theme)
**/
std::string getBgPathByTheme(const Theme &theme);

/*!
  * @brief function used to return the path of the Player depending on the theme
  * @param [in] theme: theme id
  * @fn string getPlayerSpritePathByTheme(const Theme &theme)
**/
std::string getPlayerSpritePathByTheme(const Theme &theme);

/*!
  * @brief function used to return the path of the Invader depending on the theme
  * @param [in] theme: theme id
  * @fn string getInvaderSpritePathByTheme(const Theme &theme)
**/
std::string getInvaderSpritePathByTheme(const Theme &theme);

/*!
  * @brief function used to return the path of the Player Bullets depending on the theme
  * @param [in] theme: theme id
  * @fn string getPlayerBulletSpritePathByTheme(const Theme &theme)
**/
std::string getPlayerBulletSpritePathByTheme(const Theme &theme);

/*!
  * @brief function used to return the path of the Invader Bullets depending on the theme
  * @param [in] theme: theme id
  * @fn string getInvaderBulletSpritePathByTheme(const Theme &theme)
**/
std::string getInvaderBulletSpritePathByTheme(const Theme &theme);

/*!
  * @brief function used to return the path of the Shield depending on the theme
  * @param [in] theme: theme id
  * @fn string getShieldSpritePathByTheme(const Theme &theme)
**/
std::string getShieldSpritePathByTheme(const Theme &theme);

/*!
  * @brief function pick a color depending on the theme
  * @param [in] theme: theme id
  * @fn nsGraphics::RGBAcolor getTextColorByTheme(const Theme &theme)
**/
nsGraphics::RGBAcolor getTextColorByTheme(const Theme &theme);

/*!
  * @brief function to return a string, wich stores all the charchers pressed in the same frame
  * @param [in/out] window
  * @param [in] isReset : boolen to check if a key is detected even if the key is being constantly pressed
  * @fn string getPressedChars(MinGL &window,const bool isReset)
**/
std::string getPressedChars(MinGL &window,const bool isReset);

/*!
  * @brief procedure used to initialize the elements in the main menu
  * @param[in/out] scene: the scene that contains all the elements
  * @fn void initMainMenu(Scene &scene)
**/
void initMainMenu(Scene &scene);

/*!
  * @brief procedure used to initialize the elements in the score menu
  * @param[in/out] scene: the scene that contains all the elements
  * @fn void initScoreMenu(Scene &scene)
**/
void initScoreMenu(Scene &scene);

/*!
  * @brief procedure used to initialize the elements in the settings scene
  * @param[in/out] scene: the scene that contains all the elements
  * @param[in/out] settings: dictionnary with the settings in it
  * @fn void initSettingsScene(Scene &scene,std::map<std::string,std::string> &settings)
**/
void initSettingsScene(Scene &scene,std::map<std::string,std::string> &settings);

/*!
  * @brief procedure used to initialize the elements in the game scene
  * @param[in/out] scene: the scene that contains all the elements
  * @param[in/out] gameData : informations stored between games
  * @fn void initGameScene(Scene &scene, nsSpaceInvaders::Data &gameData, const Theme &theme)
**/
void initGameScene(Scene &scene, nsSpaceInvaders::Data &gameData, const Theme &theme);

/*!
  * @brief procedure used to initialize the elements in the game over scene
  * @param[in/out] scene: the scene that contains all the elements
  * @fn void initGameOverScene(Scene &scene)
**/
void initGameOverScene(Scene &scene);

/*!
  * @brief procedure used to initialize the elements in the game over scene
  * @param[in/out] window
  * @param[in/out] scene: the scene that contains all the elements
  * @fn void displayScene(MinGL &window, const Scene &scene)
**/
void displayScene(MinGL &window, const Scene &scene);

/*!
  * @brief procedure used to initialize the elements in the game over scene
  * @param[in/out] window
  * @param[in/out] theme: theme id
  * @param[in/out] scene :the scene that contains all the elements
  * @param[in/out] currentScene: the scene we are currently in
  * @param[in/out] gameScene : the scene of the game
  * @param[in/out] scoreScene : the scene of score
  * @param[in/out] gameData : informations stored between games
  * @fn void computeMainMenu(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, Scene &gameScene,Scene &scoreScene, nsSpaceInvaders::Data &gameData)
**/
void computeMainMenu(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, Scene &gameScene,Scene &scoreScene, nsSpaceInvaders::Data &gameData);

/*!
  * @brief procedure used to initialize the elements in the game over scene
  * @param[in/out] window
  * @param[in/out] scene: the scene that contains all the elements
  * @param[in/out] currentScene: the scene we are currently in
  * @fn void computeScoreMenu(MinGL &window, Scene &scene, SceneID &currentScene)
**/
void computeScoreMenu(MinGL &window, Scene &scene, SceneID &currentScene);

/*!
  * @brief procedure used to initialize the elements in the game over scene
  * @param[in/out] window
  * @param[in/out] theme: theme id
  * @param[in/out] scene :the scene that contains all the elements
  * @param[in/out] currentScene: the scene we are currently in
  * @param[in/out] settings : dictionnary with the settings in it
  * @fn void computeSettingsMenu(MinGL &window, Theme &theme,Scene &scene, SceneID &currentScene, std::map<std::string,std::string> &settings)
**/
void computeSettingsMenu(MinGL &window, Theme &theme,Scene &scene, SceneID &currentScene, std::map<std::string,std::string> &settings);

/*!
  * @brief procedure used to initialize the elements in the game over scene
  * @param[in/out] window
  * @param[in/out] theme: theme id
  * @param[in/out] scene :the scene that contains all the elements
  * @param[in/out] currentScene: the scene we are currently in
  * @param[in/out] gameData : informations stored between games
  * @param[in/out] settings : dictionnary with the settings in it
  * @fn void computeGameScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, nsSpaceInvaders::Data &gameData, std::map<std::string,std::string> settings)
**/
void computeGameScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, nsSpaceInvaders::Data &gameData, std::map<std::string,std::string> settings);

/*!
  * @brief procedure used to initialize the elements in the game over scene
  * @param[in/out] window
  * @param[in/out] theme: theme id
  * @param[in/out] scene :the scene that contains all the elements
  * @param[in/out] currentScene: the scene we are currently in
  * @param[in/out] gameData : informations stored between games
  * @fn void computeGameOverScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, nsSpaceInvaders::Data &gameData)
**/
void computeGameOverScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, nsSpaceInvaders::Data &gameData);

}

#endif // SCENE_H
