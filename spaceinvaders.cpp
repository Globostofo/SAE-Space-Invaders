#include "spaceinvaders.h"

void nsSpaceInvaders::initShieldsList(std::vector<nsEntity::Entity> &shields, const std::string &sprite) {
    nsGraphics::Vec2D spriteSize = nsGui::Sprite(sprite).computeSize();
    for (unsigned i=0; i<nsConsts::nbOfShields; ++i)
        shields.push_back(
                    nsEntity::Entity {nsEntity::SHIELD,
                                     nsGui::Sprite(sprite, nsGraphics::Vec2D(nsConsts::WINSIZE.getX()/nsConsts::nbOfShields*i + nsConsts::WINSIZE.getX()/nsConsts::nbOfShields/2, 500)),
                                     spriteSize,
                                     3,
                                     nsBox::Box{nsGraphics::Vec2D(), nsConsts::WINSIZE-spriteSize}});
} // initShieldsList()

void nsSpaceInvaders::initInvadersList(std::vector<nsEntity::Entity> &invaders, const std::string &sprite, const Data &gameData) {
    nsGraphics::Vec2D spriteSize = nsGui::Sprite(sprite).computeSize();
    for (unsigned i=0; i<std::min(nsConsts::nbOfRowsInvaders+2*gameData.round,(unsigned)12); ++i) {
        for (unsigned j=0; j<3; ++j) {
            nsGui::Sprite invaderSprite (sprite, nsGraphics::Vec2D(100*i, spriteSize.getY()*j));
            invaders.push_back(nsEntity::Entity {
                                   nsEntity::INVADER,
                                   invaderSprite,
                                   spriteSize,
                                   3,
                                   nsBox::Box{nsGraphics::Vec2D(),
                                              nsConsts::WINSIZE-spriteSize},
                                   (int)gameData.round/2+3,
                                   nsGraphics::Vec2D(1,0)
                               }
                               );
        }
    }
}

void nsSpaceInvaders::playerMove(MinGL &window, std::vector<nsEntity::Entity> &entities,std::map<std::string,std::string> &settings) {
    for (nsEntity::Entity &entity : entities) {
//    nsEntity::Entity player = std::find_if(entities.begin(),)
        if (entity.type == nsEntity::SHIP) {
            entity.direction.setX(window.isPressed({settings["RightKey"][0], false}) - window.isPressed({settings["LeftKey"][0], false}));
            entity.direction.setY(window.isPressed({settings["DownKey"][0], false}) - window.isPressed({settings["UpKey"][0], false}));
            moveEntities(entity);
            break;
        }
    }
}

void nsSpaceInvaders::invadersMove(std::vector<nsEntity::Entity> &entities, unsigned &invadersLine) {
    // all invaders have same direction (we fix -1 for left, 0 for down, 1 for right) that's used only in this function
    short direction;
    for (const nsEntity::Entity &entity : entities)
        if (entity.type == nsEntity::INVADER) {
            direction = entity.direction.getX();
            break;
        }

    switch (direction) {

    case -1:
    case  1: {
        for (nsEntity::Entity &entity : entities)
            if (entity.type == nsEntity::INVADER)
                // if an entity reachs border, all entities go down
                if ((direction == -1 && entity.sprite.getPosition().getX() == entity.bounds.firstPosition.getX())
                        || (direction ==  1 && entity.sprite.getPosition().getX() == entity.bounds.secondPosition.getX())) {
                    nsEntity::setEntitiesDirection(entities, nsGraphics::Vec2D(0,1), nsEntity::INVADER);
                    ++invadersLine;
                    break;
                }
        break;
    }

    case 0: {
        // Lose if an invader reach bottom
        for (nsEntity::Entity &entity : entities) {
            if (entity.type == nsEntity::INVADER && entity.sprite.getPosition().getY()+entity.spriteSize.getY() == nsConsts::WINSIZE.getY()) {
                for (nsEntity::Entity &entity2 : entities)
                    if (entity2.type == nsEntity::SHIP) {
                        entity2.lifePoints = 0;
                        break;
                    }
                break;
            }
        }
        // Change direction if an invader reach a new row
        for (nsEntity::Entity &entity : entities)
            if (entity.type == nsEntity::INVADER) {
                if ((unsigned)entity.sprite.getPosition().getY() >= invadersLine * entity.spriteSize.getY()) {
                    if (invadersLine%2) nsEntity::setEntitiesDirection(entities, nsGraphics::Vec2D(-1), nsEntity::INVADER);
                    else nsEntity::setEntitiesDirection(entities, nsGraphics::Vec2D(1), nsEntity::INVADER);
                }
                break;
            }
    }

    }

    moveEntities(entities, nsEntity::INVADER);
}

void nsSpaceInvaders::playerShoot(MinGL &window, std::vector<nsEntity::Entity> &entities, const unsigned &difficulty,
                                  bool &canShoot, steady_clock::time_point &lastShot, const std::string &bulletPath) {

    if (canShoot && window.isPressed({' ',false})) {
        canShoot = false;
        lastShot = steady_clock::now();
        for (const nsEntity::Entity &entity : entities) {
            if (entity.type == nsEntity::SHIP) {
                nsGui::Sprite bulletSprite (bulletPath, entity.sprite.getPosition());
                entities.push_back(
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
        }
    }

    else if (duration_cast<milliseconds>(steady_clock::now() - lastShot).count() >= nsConsts::reloadTime-50*difficulty)
        canShoot = true;
}

void nsSpaceInvaders::invadersShoot(MinGL &window, std::vector<nsEntity::Entity> &entities,
                                    bool &canShoot, steady_clock::time_point &lastShot, const std::string &bulletPath) {

    if (canShoot) {
        canShoot = false;
        lastShot = steady_clock::now();
        std::vector<unsigned> invadersRanks;
        for (size_t i=0; i<entities.size(); ++i)
            if (entities[i].type == nsEntity::INVADER)
                invadersRanks.push_back(i);
        nsGui::Sprite bulletSprite (bulletPath, entities[invadersRanks[rand()%invadersRanks.size()]].sprite.getPosition());
        entities.push_back(
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
