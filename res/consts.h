#ifndef CONSTS_H
#define CONSTS_H

#include <string>
#include "mingl/graphics/vec2d.h"

namespace nsConsts {

const nsGraphics::Vec2D WINSIZE(1280, 720);

// Backgrounds paths
const std::string bg1 = "res/fond.si2";
const std::string bg2 = "res/fond-ciel.si2";
const std::string bg3 = "res/fond-mer.si2";
const std::string bg4 = "res/windowBG.si2";

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
const std::string shieldSprite1 = "";   // classic shield
const std::string shieldSprite2 = "res/windo-Def.si2";

const unsigned nbOfInvaders = 5;

const unsigned reloadTime = 1000;   // milliseconds

} // namespace nsConsts

#endif // CONSTS_H
