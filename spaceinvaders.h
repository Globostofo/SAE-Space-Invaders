#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H


#include "mingl/mingl.h"
#include "box.h"
#include "entity.h"
#include "consts.h"
#include "mingl/gui/sprite.h"
#include <thread>
using namespace std::chrono;

namespace nsSpaceInvaders {

/*!
 * @brief Create shields to start a game
 * @param[in] window : used to get size of window
 * @param[in/out] shields : list of shields
 * @fn void initShieldsList(const MinGL &window, std::vector<nsEntity::Entity> &shields);
 */
void initShieldsList(const MinGL &window, std::vector<nsEntity::Entity> &shields);

/*!
 * @brief Create invaders to start a game
 * @param[in] window : used to get size of window
 * @param[in/out] invaders : list of invaders
 * @fn void initInvadersList(const MinGL &window, std::vector<nsEntity::Entity> &invaders);
 */
void initInvadersList(const MinGL &window, std::vector<nsEntity::Entity> &invaders);

/*!
 * @brief Procedure to get user input and apply it to given entity direction
 * @param[in/out] window : used to get pressed keys
 * @param[in/out] player : entity to move
 * @fn void playerMove(MinGL &window, nsEntity::Entity &player);
 */
void playerMove(MinGL &window, nsEntity::Entity &player);

/*!
 * @brief Procedure to move invaders
 * @param[in/out] invaders : invaders to move
 * @param[in/out] invadersLine : row where they are (usefull to go down when an invader reach border)
 * @fn void invadersMove(std::vector<nsEntity::Entity> &invaders, unsigned &invadersLine);
 */
void invadersMove(std::vector<nsEntity::Entity> &invaders, unsigned &invadersLine);

/*!
 * @brief Procedure to get user input and make player shoot
 * @param[in/out] window : used to get pressed keys
 * @param[in/out] player : entity who shoots
 * @param[in/out] bullets : vector with all bullets
 * @param[in/out] canShoot : boolean to block shot
 * @param[in/out] lastShot : chrono to put delay to shots
 * @fn void playerShoot(MinGL &window, nsEntity::Entity &player, std::vector<nsEntity::Entity> &bullets, bool &canShoot, steady_clock::time_point &lastShot);
 */
void playerShoot(MinGL &window, nsEntity::Entity &player,
                 std::vector<nsEntity::Entity> &bullets,
                 bool &canShoot,
                 steady_clock::time_point &lastShot);

/*!
 * @brief Procedure to make invaders shoot
 * @param[in/out] window : used to get window size
 * @param[in/out] invaders : vector with all invaders entities
 * @param[in/out] bullets : vector with all invaders bullets entities
 * @param[in/out] canShoot : booleen to block shot
 * @param[in/out] lastShot : chorno to put delay to shots
 * @fn void invadersShoot(MinGL &window, std::vector<nsEntity::Entity> &invaders, std::vector<nsEntity::Entity> &bullets, bool &canShoot, steady_clock::time_point &lastShot);
 */
void invadersShoot(MinGL &window, std::vector<nsEntity::Entity> &invaders,
                   std::vector<nsEntity::Entity> &bullets,
                   bool &canShoot,
                   steady_clock::time_point &lastShot);


} // namespace nsSpaceInvaders

#endif // SPACEINVADERS_H
