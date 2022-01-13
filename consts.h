/*!
 *
 * @file    consts.h
 * @author  Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
 * @date    January 2022
 * @brief   Constants
 *
 **/

#ifndef CONSTS_H
#define CONSTS_H

#include <string>

#include "mingl/graphics/vec2d.h"
#include "mingl/gui/glut_font.h"
#include "mingl/graphics/rgbacolor.h"

namespace nsConsts {

const nsGraphics::Vec2D WINSIZE(1280, 720);

// Ressources
const std::string config = "res/config.yaml";
const std::string leaderboard = "res/leaderBoard.txt";

// Backgrounds paths
const std::string bgMenu = "res/menuBG.si2";
const std::string bg1 = "res/fond.si2";
const std::string bg2 = "res/fond-ciel.si2";
const std::string bg3 = "res/fond-mer.si2";
const std::string bg4 = "res/windowsBG.si2";

// Player sprites paths
const std::string playerSprite1 = "res/player.si2";
const std::string playerSprite2 = "res/player-ciel.si2";
const std::string playerSprite3 = "res/player-mer.si2";
const std::string playerSprite4 = "res/Windo.si2";

// Invaders sprites paths
const std::string invaderSprite1 = "res/ennemi.si2";
const std::string invaderSprite2 = "res/ennemi-ciel.si2";
const std::string invaderSprite3 = "res/ennemi-mer.si2";
const std::string invaderSprite4 = "res/linux.si2";

// Player bullet sprites paths
const std::string playerBulletSprite1 = "res/player-bullet.si2";
const std::string playerBulletSprite2 = "res/laser-windo.si2";

// Invader bullet sprites paths
const std::string invaderBulletSprite1 = "res/ennemi-bullet.si2";
const std::string invaderBulletSprite2 = "res/ls-aux.si2";

// Shield sprites paths
const std::string shieldSprite1 = "res/shield.si2";
const std::string shieldSprite2 = "res/windo-def.si2";

// Text properties
const nsGraphics::RGBAcolor textColor = nsGraphics::KBlack;
const nsGui::GlutFont::GlutFonts textFont = nsGui::GlutFont::BITMAP_9_BY_15;

// Buttons properties
const nsGraphics::RGBAcolor btBgColor = nsGraphics::KSilver;
const nsGraphics::RGBAcolor btBorderColor = nsGraphics::KBlack;

// Game settings
const int playerSpeed = 15;
const unsigned nbLifes = 5;
const unsigned nbOfRowsInvaders = 3;
const unsigned nbOfColumnsInvaders = 3;
const unsigned nbOfShields = 4;
const unsigned reloadTime = 1000;   // milliseconds
const unsigned maxNameSize = 20;

// Game points
const unsigned invaderHurt = 10;
const unsigned invaderDeath = 100;
const unsigned levelClear = 500;

} // namespace nsConsts

#endif // CONSTS_H
