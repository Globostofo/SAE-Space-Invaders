#include "scene.h"
#include "file.h"

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

string nsScene::getPressedChars(MinGL &window, const bool isReset) {
    string alphabet = " abcdefghijklmnopqrstuvwxyz\b";
    string output;
    for(const char &let : alphabet)
        if (window.isPressed({let, false})) {
            output += let;
            if(isReset)
                window.resetKey(MinGL::KeyType_t({let, false}));
        }
    return output;
} // getLastPressedChar()

void nsScene::initMainMenu(Scene &scene) {
    vector<nsButton::Button> btns = {{"Play"}, {"LeaderBoard"},{"Settings"}};
    nsButton::placeBtns(btns);
    scene.buttons = btns;
}

void nsScene::initScoreMenu(Scene &scene) {
    vector<string> leaderboard(10);
    nsFile::getLeaderBoard(leaderboard);
    vector<nsButton::Button> btns(leaderboard.size()+1);
    for(size_t i = 0; i<leaderboard.size() ; ++i){
        btns[i]={leaderboard[i]};
    }
    btns[leaderboard.size()]={"Back"};
    nsButton::placeBtns(btns);
    scene.buttons = btns;
}

void nsScene::initSettingsScene(Scene &scene, map<string,string> &settings){
    map<string,string> scenes;
    scenes["0"]="Base";
    scenes["1"]="Sky";
    scenes["2"]="Sea";
    scenes["3"]="W vs L";

    vector<nsButton::Button> btns = {{"LeftKey:"+settings.find("LeftKey")->second},
                                     {"RightKey:"+settings.find("RightKey")->second},
                                     {"DownKey:"+settings.find("DownKey")->second},
                                     {"UpKey:"+settings.find("UpKey")->second},
                                     {"ShootKey:"+settings.find("ShootKey")->second},
                                     {"Theme:"+scenes[settings.find("Theme")->second]},
                                     {"Back"}};
    nsButton::placeBtns(btns);
    scene.buttons = btns;
    scene.texts = {nsGui::Text(nsGraphics::Vec2D(10,10), "Press the key and the button\nsimultaneously to change the setting", nsGraphics::KWhite, nsConsts::textFont, nsGui::Text::ALIGNH_LEFT,nsGui::Text::ALIGNV_TOP)};
}

void nsScene::initGameScene(Scene &scene, nsSpaceInvaders::Data &gameData, const Theme &theme) {
    nsButton::Button bt {"Exit"};
    nsButton::setPosition(bt, nsGraphics::Vec2D(67,48));
    scene.buttons = {bt};

    nsGui::Sprite pSprite(getPlayerSpritePathByTheme(theme), nsGraphics::Vec2D(nsConsts::WINSIZE.getX()/2, nsConsts::WINSIZE.getY() - 60));
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

void nsScene::initGameOverScene(Scene &scene) {
    vector<nsButton::Button> btns {{"Play again"}, {"Main menu"}};
    nsButton::placeBtns(btns);
    scene.buttons = btns;
    scene.texts = {nsGui::Text(nsConsts::WINSIZE/2, "Enter your name :", nsConsts::textColor, nsConsts::textFont, nsGui::Text::ALIGNH_CENTER),
                   nsGui::Text(nsConsts::WINSIZE/2, "", nsConsts::textColor, nsConsts::textFont, nsGui::Text::ALIGNH_CENTER, nsGui::Text::ALIGNV_TOP)};
}

void nsScene::displayScene(MinGL &window, const Scene &scene) {
    window << scene.background;
    nsEntity::dispEntities(window, scene.entities);
    nsButton::drawBtns(window, scene.buttons);
    for (const nsGui::Text &text : scene.texts)
        window << text;
}

void nsScene::computeMainMenu(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, Scene &gameScene, nsSpaceInvaders::Data &gameData) {
    if (nsButton::isPressed(window.getEventManager(), scene.buttons[0])) {
        currentScene = GAME;
        gameData.round = 0;
        gameData.lifePointsRemaining = nsConsts::nbLifes;
        gameData.score = 0;
        initGameScene(gameScene, gameData, theme);
    }
    else if (nsButton::isPressed(window.getEventManager(), scene.buttons[1])) {
        currentScene = SCORE_MENU;
        std::vector<string> leaderboard;
        nsFile::getLeaderBoard(leaderboard);
    }
    else if(nsButton::isPressed(window.getEventManager(), scene.buttons[2])){
        currentScene = SETTINGS_MENU;
    }
    displayScene(window, scene);
}

void nsScene::computeScoreMenu(MinGL &window, Scene &scene, SceneID &currentScene) {
    if (nsButton::isPressed(window.getEventManager(), scene.buttons[10]))
        currentScene = MAIN_MENU;
    displayScene(window, scene);
}

void nsScene::computeSettingsMenu(MinGL &window, Scene &scene, SceneID &currentScene, map<string,string> settings) {
    int themeCounter = stoi(settings["Theme"]);

    string inputs = getPressedChars(window,false);
    cout<<inputs<<endl;
    if(inputs.size()>0){
        for(unsigned i = 0 ; i<scene.buttons.size()-2; ++i){        // -2 bc last 2 not keys
            if (nsButton::isPressed(window.getEventManager(), scene.buttons[i])){
                string key =scene.buttons[i].text.getContent().substr(0,scene.buttons[i].text.getContent().size()-2);
                settings[key]=inputs[0];
                scene.buttons[i].text.setContent(key +":"+ settings[key]);
            }
        }
    }
    if(nsButton::isPressed(window.getEventManager(), scene.buttons[5])){

       ++themeCounter%=4;
        unsigned separator=scene.buttons[5].text.getContent().find(":");
        settings["Theme"]=to_string(themeCounter);

        switch (themeCounter) {
            case 0:{
                scene.buttons[5].text.setContent(scene.buttons[5].text.getContent().substr(0,separator+1)+"Base");
                break;
            }
            case 1:{
                scene.buttons[5].text.setContent(scene.buttons[5].text.getContent().substr(0,separator+1)+"Sky");
                break;
            }
            case 2:{
                scene.buttons[5].text.setContent(scene.buttons[5].text.getContent().substr(0,separator+1)+"Sea");
                break;
            }
            case 3:{
                scene.buttons[5].text.setContent(scene.buttons[5].text.getContent().substr(0,separator+1)+"W vs L");
                break;
            }
        }
    }
    if(nsButton::isPressed(window.getEventManager(), scene.buttons[6])){
        nsFile::writeConfigFile(settings);
        currentScene = MAIN_MENU;
    }
    displayScene(window, scene);
}

void nsScene::computeGameScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, nsSpaceInvaders::Data &gameData, map<string,string> settings) {
    if (nsButton::isPressed(window.getEventManager(), scene.buttons[0])) {currentScene = MAIN_MENU; return;}

    // Move entities
    nsSpaceInvaders::playerMove(window, scene.entities,settings); //passer en parametre settings pour touches
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
        currentScene = GAME_OVER_MENU;
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

    // Disaplay scene
    displayScene(window, scene);
}

void nsScene::computeGameOverScene(MinGL &window, const Theme &theme, Scene &scene, SceneID &currentScene, nsSpaceInvaders::Data &gameData) {
    if (nsButton::isPressed(window.getEventManager(), scene.buttons[0])) {
        // update leaderBoard.txt
        vector<string> leaderboard (10);
        nsFile::getLeaderBoard(leaderboard);
        nsFile::addScore(leaderboard,scene.texts[1].getContent(), gameData.score);
        nsFile::writeLeaderBoard(leaderboard);

        currentScene = GAME;
        gameData.round = 0;
        gameData.lifePointsRemaining = nsConsts::nbLifes;
        gameData.score = 0;
        initGameScene(scene, gameData, theme);
    }
    else if (nsButton::isPressed(window.getEventManager(), scene.buttons[1])) {
        // update leaderBoard.txt
        vector<string> leaderboard (10);
        nsFile::getLeaderBoard(leaderboard);
        nsFile::addScore(leaderboard,scene.texts[1].getContent(), gameData.score);
        nsFile::writeLeaderBoard(leaderboard);
        currentScene = MAIN_MENU;
    }

    string inputs = getPressedChars(window,true);
    for (const char &pressed : inputs) {
        string content = scene.texts[1].getContent();
        if (pressed == '\b' && content.size())
            scene.texts[1].setContent(content.substr(0, content.size()-1));
        else if (pressed != '\b' && content.size() < nsConsts::maxNameSize)
            scene.texts[1].setContent(content + pressed);
    }

    displayScene(window, scene);
}
