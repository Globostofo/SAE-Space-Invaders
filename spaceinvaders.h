/*!
 *
 * @file    spaceInvaders.h
 * @author  Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
 * @date    January 2022
 * @brief   SpaceInvaders Game
 *
 **/

#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <thread>
#include <map>

#include "mingl/mingl.h"
#include "mingl/gui/sprite.h"

#include "box.h"
#include "entity.h"
#include "consts.h"

using namespace std::chrono;

namespace nsSpaceInvaders {

/*!
 * @struct Data
 * @brief stores the information between differents rounds
 */
struct Data {
    unsigned round;
    int lifePointsRemaining;
    unsigned score;
    bool canShoot = true;
    steady_clock::time_point lastShot = steady_clock::now();
    bool invadersCanShoot = false;
    steady_clock::time_point invadersLastShot = steady_clock::now();
    unsigned invadersLine = 0;
};

/*!
 * @brief Create shields to start a game
 * @param[in/out] shields : list of shields
 * @param[in] sprite : directory of the shield sprite
 * @fn void initShieldsList(std::vector<nsEntity::Entity> &shields, const std::string &sprite)
 */
void initShieldsList(std::vector<nsEntity::Entity> &shields, const std::string &sprite);

/*!
 * @brief Create invaders to start a game
 * @param[in/out] invaders : list of invaders
 * @param[in] sprite : directory of the invader sprite
 * @param[in] gamedata : struct Data containing the information between differents rounds
 * @fn void initInvadersList(std::vector<nsEntity::Entity> &invaders, const std::string & sprite, const Data &gameData)
 */
void initInvadersList(std::vector<nsEntity::Entity> &invaders, const std::string & sprite, const Data &gameData);

/*!
 * @brief Procedure to get user input and apply it to given entity direction
 * @param[in/out] window : used to get pressed keys
 * @param[in/out] enities : entity to move
 * @param[in] settings : dictionnary containing the keys used by a player to move
 * @fn void playerMove(MinGL &window, std::vector<nsEntity::Entity> &entities,std::map<std::string,std::string> settings)
 */
void playerMove(MinGL &window, std::vector<nsEntity::Entity> &entities,const std::map<std::string,std::string> settings);

/*!
 * @brief Procedure to move invaders
 * @param[in/out] entities : entities to move
 * @param[in/out] invadersLine : row where they are (usefull to go down when an invader reach border)
 * @fn void invadersMove(std::vector<nsEntity::Entity> &invaders, unsigned &invadersLine);
 */
void invadersMove(std::vector<nsEntity::Entity> &entities, unsigned &invadersLine);

/*!
 * @brief Procedure to get user input and make player shoot
 * @param[in/out] window : used to get pressed keys
 * @param[in/out] player : entity who shoots
 * @param[in/out] difficulty : shoot speed depends on the round (faster = harder it gets)
 * @param[in/out] canShoot : boolean to block shot
 * @param[in/out] lastShot : chrono to put delay to shots
 * @fn void playerShoot(MinGL &window, std::vector<nsEntity::Entity> &entities, const unsigned &difficulty, bool &canShoot, steady_clock::time_point &lastShot, const std::string &bulletPath
 */
void playerShoot(MinGL &window, std::vector<nsEntity::Entity> &entities, const unsigned &difficulty,
                 bool &canShoot, steady_clock::time_point &lastShot, const std::string &bulletPath);

/*!
 * @brief Procedure to make invaders shoot
 * @param[in/out] window : used to get window size
 * @param[in/out] invaders : list with all invaders entities
 * @param[in/out] canShoot : booleen to block shot
 * @param[in/out] lastShot : chorno to put delay to shots
 * @param[in/out] bulletPath : path of the bullet
 * @fn void invadersShoot(MinGL &window, std::vector<nsEntity::Entity> &invaders, std::vector<nsEntity::Entity> &bullets, bool &canShoot, steady_clock::time_point &lastShot, const std::string &bulletPath)
 */
void invadersShoot(MinGL &window, std::vector<nsEntity::Entity> &entities,
                   bool &canShoot, steady_clock::time_point &lastShot, const std::string &bulletPath);


} // namespace nsSpaceInvaders

#endif // SPACEINVADERS_H
