#include "spaceinvaders.h"

void nsSpaceInvaders::initShieldsList(const MinGL &window, std::vector<nsEntity::Entity> &shields) {
    nsGraphics::Vec2D spriteSize = nsGui::Sprite(nsConsts::shieldSprite).computeSize();
    for (short i=0; i<3; ++i)
        shields.push_back(
                    nsEntity::Entity {nsEntity::SHIELD,
                                     nsGui::Sprite(nsConsts::shieldSprite, nsGraphics::Vec2D(300*i, 400)),
                                     spriteSize,
                                     3,
                                     nsBox::Box{nsGraphics::Vec2D(), window.getWindowSize()-spriteSize}});
} // initShieldsList()

void nsSpaceInvaders::initInvadersList(const MinGL &window, std::vector<nsEntity::Entity> &invaders) {
    nsGraphics::Vec2D spriteSize = nsGui::Sprite(nsConsts::invaderSprite).computeSize();
    for (unsigned i=0; i<nsConsts::nbOfInvaders; ++i) {
        nsGui::Sprite invaderSprite (nsConsts::invaderSprite, nsGraphics::Vec2D(100*i));
        invaders.push_back(nsEntity::Entity {
                               nsEntity::INVADER,
                               invaderSprite,
                               spriteSize,
                               3,
                               nsBox::Box{nsGraphics::Vec2D(),
                                        window.getWindowSize()-spriteSize},
                               1,
                               nsGraphics::Vec2D(1,0)
                           }
                           );
    }
}

void nsSpaceInvaders::playerMove(MinGL &window, nsEntity::Entity &player) {
    player.direction.setX(window.isPressed({'d', false}) - window.isPressed({'q', false}));
    player.direction.setY(window.isPressed({'s', false}) - window.isPressed({'z', false}));
    moveEntities(player);
}

void nsSpaceInvaders::invadersMove(std::vector<nsEntity::Entity> &invaders, unsigned &invadersLine) {
    // all invaders have same direction (we fix -1 for left, 0 for down, 1 for right) that's used only in this function
    short direction = invaders[0].direction.getX();

    switch (direction) {

    case -1:
    case  1: {
        for (nsEntity::Entity &invader : invaders)
            // if an entity reachs border, all entities go down
            if ((direction == -1 && invader.sprite.getPosition().getX() == invader.bounds.firstPosition.getX())
                    || (direction ==  1 && invader.sprite.getPosition().getX() == invader.bounds.secondPosition.getX())) {
                nsEntity::setEntitiesDirection(invaders, nsGraphics::Vec2D(0,1));
                ++invadersLine;
                break;
            }
        break;
    }

    case 0: {
        for (nsEntity::Entity &invader : invaders)
            if ((unsigned)invader.sprite.getPosition().getY() >= invadersLine * invader.spriteSize.getY()) {
                if (invadersLine%2) nsEntity::setEntitiesDirection(invaders, nsGraphics::Vec2D(-1));
                else nsEntity::setEntitiesDirection(invaders, nsGraphics::Vec2D(1));
                break;
            }
    }

    }

    moveEntities(invaders);
}

void nsSpaceInvaders::playerShoot(MinGL &window, nsEntity::Entity &player,
                 std::vector<nsEntity::Entity> &bullets,
                 bool &canShoot,
                 steady_clock::time_point &lastShot) {

    if (canShoot && window.isPressed({' ',false})) {
        canShoot = false;
        lastShot = steady_clock::now();
        nsGui::Sprite bulletSprite (nsConsts::playerBulletSprite, player.sprite.getPosition());
        bullets.push_back(
                    nsEntity::Entity {
                        nsEntity::SHIP_BULLET,
                        bulletSprite,
                        bulletSprite.computeSize(),
                        1,
                        nsBox::Box {nsGraphics::Vec2D(0,0),
                                  window.getWindowSize()},
                        10,
                        nsGraphics::Vec2D(0,-1),
                        true
                    }
                    );
    }

    else if (duration_cast<milliseconds>(steady_clock::now() - lastShot).count() >= nsConsts::reloadTime)
        canShoot = true;
}

void nsSpaceInvaders::invadersShoot(MinGL &window, std::vector<nsEntity::Entity> &invaders,
                   std::vector<nsEntity::Entity> &bullets,
                   bool &canShoot,
                   steady_clock::time_point &lastShot) {

    if (canShoot) {
        canShoot = false;
        lastShot = steady_clock::now();
        nsGui::Sprite bulletSprite (nsConsts::enemyBulletSprite, invaders[rand()%invaders.size()].sprite.getPosition());
        bullets.push_back(
                    nsEntity::Entity {
                        nsEntity::INVADER_BULLET,
                        bulletSprite,
                        bulletSprite.computeSize(),
                        1,
                        nsBox::Box {nsGraphics::Vec2D(0,0),
                                  window.getWindowSize()},
                        10,
                        nsGraphics::Vec2D(0,1),
                        true
                    }
                    );
    }

    else if (duration_cast<milliseconds>(steady_clock::now() - lastShot).count() >= nsConsts::reloadTime)
        canShoot = true;
}
