#include "enemy.h"

nsGame::Enemy nsGame::createEnemy(const EnemySprites & sprite, const int & lifes) {
    switch (sprite) {
        case LINUX:
            return Enemy {nsGui::Sprite("res/linux.si2"), lifes};
    }
}

void nsGame::displayEnemy(MinGL & window, const Enemy & enemy) {
    window << enemy.sprite;
}

nsGui::Sprite nsGame::getEnemySprite(const Enemy & enemy) {
    return enemy.sprite;
}

void nsGame::setEnemySprite(Enemy & enemy, const EnemySprites & sprite) {
    switch (sprite) {
        case LINUX:
            enemy.sprite = nsGui::Sprite("res/linux.si2");
            break;
    }
}

int nsGame::getEnemyLifes(const Enemy & enemy) {
    return enemy.lifes;
}

void nsGame::setEnemyLifes(Enemy & enemy, const int & lifes) {
    enemy.lifes = lifes;
}

nsGraphics::Vec2D nsGame::getEnemySize(const Enemy & enemy) {
    return enemy.sprite.computeSize();
}
