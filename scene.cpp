#include "scene.h"

using namespace std;

string nsScene::getBgPathByTheme(const Theme &theme) {
    switch (theme) {
        case BASE:
            return nsConsts::bg1;
        case SKY:
            return nsConsts::bg2;
        case SEA:
            return nsConsts::bg3;
        case WINDOWS:
            return nsConsts::bg4;
    }
}

string nsScene::getPlayerSpritePathByTheme(const Theme &theme) {
    switch (theme) {
        case BASE:
            return nsConsts::playerSprite1;
        case SKY:
            return nsConsts::playerSprite2;
        case SEA:
            return nsConsts::playerSprite3;
        case WINDOWS:
            return nsConsts::playerSprite4;
    }
}

string nsScene::getInvaderSpritePathByTheme(const Theme &theme) {
    switch (theme) {
        case BASE:
            return nsConsts::invaderSprite1;
        case SKY:
            return nsConsts::invaderSprite2;
        case SEA:
            return nsConsts::invaderSprite3;
        case WINDOWS:
            return nsConsts::invaderSprite4;
    }
}

string nsScene::getPlayerBulletSpritePathByTheme(const Theme &theme) {
    switch (theme) {
        case BASE:
        case SKY:
        case SEA:
            return nsConsts::playerBulletSprite1;
        case WINDOWS:
            return nsConsts::playerBulletSprite2;
    }
}

string nsScene::getInvaderBulletSpritePathByTheme(const Theme &theme) {
    switch (theme) {
        case BASE:
        case SKY:
        case SEA:
            return nsConsts::invaderBulletSprite1;
        case WINDOWS:
            return nsConsts::invaderBulletSprite2;
    }
}

string nsScene::getShieldSpritePathByTheme(const Theme &theme) {
    switch (theme) {
        case BASE:
        case SKY:
        case SEA:
            return nsConsts::shieldSprite1;
        case WINDOWS:
            return nsConsts::shieldSprite2;
    }
}

void nsScene::initMainMenu(Scene &scene) {
    vector<nsButton::Button> btns = {
        nsButton::Button {"Play"},
        nsButton::Button {"LeaderBoard"},
        nsButton::Button {"Settings"}
    };
    nsButton::placeBtns(btns);
    scene.buttons = btns;
}

void nsScene::initSettingsMenu(Scene &scene) {
    nsButton::Button bt {"Back"};
    nsButton::setPosition(bt, nsGraphics::Vec2D(67,48));
    scene.buttons = {bt};
}

void nsScene::initScoreMenu(Scene &scene) {
    nsButton::Button bt {"Back"};
    nsButton::setPosition(bt, nsGraphics::Vec2D(67,48));
    scene.buttons = {bt};
}

void nsScene::initGameScene(Scene &scene, nsSpaceInvaders::Data &gameData, const Theme &theme) {
    nsButton::Button bt {"Exit"};
    nsButton::setPosition(bt, nsGraphics::Vec2D(67,48));
    scene.buttons = {bt};

    nsGui::Sprite pSprite(getPlayerSpritePathByTheme(theme), nsGraphics::Vec2D());
    nsGraphics::Vec2D spriteSize = pSprite.computeSize();
    std::vector<nsEntity::Entity> entities;
    entities.push_back(nsEntity::Entity {
        nsEntity::SHIP,
        pSprite,
        spriteSize,
        gameData.lifePointsRemaining,
        nsBox::Box {nsGraphics::Vec2D(10, nsConsts::WINSIZE.getY()-spriteSize.getY()-100),
                    nsConsts::WINSIZE - spriteSize - nsGraphics::Vec2D(10,10)},
        nsConsts::playerSpeed
    });
    nsSpaceInvaders::initShieldsList(entities, getShieldSpritePathByTheme(theme));

    // Invaders initialization
    nsSpaceInvaders::initInvadersList(entities, getInvaderSpritePathByTheme(theme), gameData);

    scene.entities = entities;
    scene.texts = {nsGui::Text(nsGraphics::Vec2D(nsConsts::WINSIZE.getX()-10, 10), to_string(gameData.score) + " pts", nsConsts::textColor, nsConsts::textFont, nsGui::Text::ALIGNH_RIGHT, nsGui::Text::ALIGNV_TOP),
                  {nsGui::Text(nsGraphics::Vec2D(nsConsts::WINSIZE.getX()-10, 30), to_string(gameData.lifePointsRemaining) + "lives", nsConsts::textColor, nsConsts::textFont, nsGui::Text::ALIGNH_RIGHT, nsGui::Text::ALIGNV_TOP)}};

    ++gameData.round;
    gameData.invadersLine = 0;
}

void nsScene::displayScene(MinGL &window, const Scene &scene) {
    window << scene.background;
    nsEntity::dispEntities(window, scene.entities);
    nsButton::drawBtns(window, scene.buttons);
    for (const nsGui::Text &text : scene.texts)
        window << text;
}

void nsScene::computeScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, Scene &gameScene, nsSpaceInvaders::Data &gameData) {
    switch (currentScene) {

        case MAIN_MENU: {
            if (nsButton::isPressed(window.getEventManager(), scene.buttons[0])) {
                currentScene = GAME;
                gameData.round = 0;
                gameData.lifePointsRemaining = nsConsts::nbLifes;
                gameData.score = 0;
                initGameScene(gameScene, gameData, theme);
            }
            else if (nsButton::isPressed(window.getEventManager(), scene.buttons[1])) {currentScene = SCORE_MENU;}
            else if (nsButton::isPressed(window.getEventManager(), scene.buttons[2])) {currentScene = SETTINGS_MENU;}
            break;
        }

        case SCORE_MENU:
        case SETTINGS_MENU: {
            if (nsButton::isPressed(window.getEventManager(), scene.buttons[0])) {currentScene = MAIN_MENU;}
            break;
        }

        case GAME: {
            if (nsButton::isPressed(window.getEventManager(), gameScene.buttons[0])) {currentScene = MAIN_MENU; return;}

            // Move entities
            nsSpaceInvaders::playerMove(window, scene.entities);
            nsSpaceInvaders::invadersMove(scene.entities, gameData.invadersLine);
            nsEntity::moveEntities(scene.entities, nsEntity::SHIP_BULLET);
            nsEntity::moveEntities(scene.entities, nsEntity::INVADER_BULLET);

            // Shoots
            nsSpaceInvaders::playerShoot(window, scene.entities, gameData.round, gameData.canShoot, gameData.lastShot, getPlayerBulletSpritePathByTheme(theme));
            nsSpaceInvaders::invadersShoot(window, scene.entities, gameData.invadersCanShoot, gameData.invadersLastShot, getInvaderBulletSpritePathByTheme(theme));

            // Check collisions
            nsEntity::entitiesCollisions(scene.entities, gameData.score);

            // Delete all entities where lives=0
            nsEntity::deleteDiedEntities(scene.entities, gameData.score);

            // Layout update
            scene.texts[0].setContent(to_string(gameData.score) + " pts");
            for (const nsEntity::Entity &entity : scene.entities)
                if (entity.type == nsEntity::SHIP) {
                    scene.texts[1].setContent(to_string(entity.lifePoints) + " lives");
                    break;
                }

            // End game
            bool hasLose = true;
            for (const nsEntity::Entity &entity : scene.entities)
                if (entity.type == nsEntity::SHIP) {
                    hasLose = false;
                    break;
                }
            if (hasLose) {
                cout << "YOU LOSE NOOB" << endl;
                currentScene = MAIN_MENU;
            }

            bool hasWon = true;
            for (const nsEntity::Entity &entity : scene.entities)
                if (entity.type == nsEntity::INVADER) {
                    hasWon = false;
                    break;
                }
            if (hasWon) {
                gameData.score += nsConsts::levelClear * gameData.round;
                for (const nsEntity::Entity &entity : scene.entities)
                    if (entity.type == nsEntity::SHIP) {
                        gameData.lifePointsRemaining = entity.lifePoints;
                        break;
                    }
                initGameScene(scene, gameData, theme);
                cout << "GG next level (" << gameData.round << ")" << endl;
            }

            break;
        }

    }
    displayScene(window, scene);
}
