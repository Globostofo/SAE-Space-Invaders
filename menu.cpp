/*!
  * @author Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
  * @date 9 jan 2021
  * @brief fichier permettant de créer des menus pour commencer le jeu
**/

#include "menu.h"   //all the functions and the button struct

using namespace std;

/*!
  * @brief fonction pour verifier si on appuye sur la fenetre de jeu et si un bouton est concerné
  * @param[in/out] EventManager
  * @param[in] btns : vecteur contenant les boutons
  * @fn int events(nsEvent::EventManager &eventM, const vector<button> &btns)
**/
int events(nsEvent::EventManager &eventM, const vector<button> &btns)
{
    // On vérifie chaque évènement de la queue d'évènements
    while (eventM.hasEvent())
    {
        const nsEvent::Event_t event = eventM.pullEvent();

        // On regarde le type d'évènement
        nsEvent::MouseClickData_t data = event.eventData.clickData;
        nsGraphics::Vec2D eventPos{data.x, data.y};
        if(event.eventType==nsEvent::EventType_t::MouseClick && !data.button && !data.state){
            //cout << endl << "A click : " << eventPos << endl;
            for(const button & btn : btns) {
                //cout << btn.content << " at pos : " << btn.rect.getFirstPosition() << " | " << btn.rect.getSecondPosition() << endl;
                if (eventPos.isColliding(btn.rect.getFirstPosition(), btn.rect.getSecondPosition())){
                    //cout << btn.content << endl;
                    return btn.buttonId;
                }
            }
        }
    }
    return -1;
}//events

/*!
  * @brief fonction pour recuperer la derniere touche qui as été appuyé sur le clavier
  * @param[in/out] window
  * @fn char getLastPressedChar(MinGL &window)
**/
char getLastPressedChar(MinGL &window){
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(auto letter : alphabet){
        if (window.isPressed({letter, false})){
            return letter;
        }
    }
    return ' ';
}//getLastPressedChar

/*!
  * @brief fonction pour placer des boutons centrés horizontalement et verticalement
  * @param[in/out] window : fenetre
  * @param[in] b : vecteur de struct contenant le texte à afficher et la couleur dans laquelle l'afficher
  * @param[in] width : largeur de la fenetre
  * @param[in] height : hauteur de la fenetre
**/
void placeBtns(const MinGL &window, vector<button> &btns) {

    nsGraphics::Vec2D winSize = window.getWindowSize();
    size_t nb_btns = btns.size();

    unsigned text_max_size = 0;
    for (const button &btn : btns)
        if (btn.content.size() > text_max_size)
            text_max_size = btn.content.size();
    nsGraphics::Vec2D btnSize{8*text_max_size+64, 64};

    for(size_t i=0; i<nb_btns; ++i) {

        nsGraphics::Vec2D pos1 = {winSize.getX()/2 - btnSize.getX()/2, i * winSize.getY()/nb_btns + winSize.getY()/(2*nb_btns) - btnSize.getY()/2};
        nsGraphics::Vec2D pos2 = pos1 + btnSize;
        nsGraphics::Vec2D textPos = pos1 + btnSize/2;

        btns[i].rect.setFirstPosition(pos1);
        btns[i].rect.setSecondPosition(pos2);
        btns[i].text.setPosition(textPos);

    }

}//placeBtns

/*!
  * @brief fonction utilisé pour afficher les boutons dans la fenetre : window
  * @param[in/out] window
  * @param[in] btns : vecteur contenant la liste des boutons à afficher
  * @fn void drawBtns(MinGL &window, const vector<button> &btns)
**/
void drawBtns(MinGL &window, const vector<button> &btns) {
    for (const button &btn : btns)
        window << btn.rect << btn.text;
}//DrawBtns

/*!
  * @brief fonction utilisé pour lire le fichier leaderBoard
  * @param[in/out] leaderBoard : liste avec les noms des players et leur score, avec indice 0 pour le meilleur et 9 pour le pire
  * @fn void getLeaderBoard(vector<string> &leaderBoard)
**/
void getLeaderBoard(vector<string> &leaderBoard){
    //leaderBoard init to 10
    string score;
    ifstream scoreFile ("leaderBoard.txt");
    for(vector<string>::iterator iter = leaderBoard.begin(); iter !=leaderBoard.end(); ++iter){
        getline(scoreFile,score);
        (*iter)=score;
    }
}//getLeaderBoard

/*!
  * @brief fonction utilisé pour commencer le jeu
  * @param[in/out] window
  * @fn void startButton(MinGL &window
**/
void startButton(MinGL &window){
    vector<button> btns(4);
    btns[0] = button {"Enter your Name :",0, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[1] = button {" ",1, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[2] = button {"Play",-1, nsGraphics::KRed, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[3] = button {"Back",3, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    placeBtns(window, btns);

    bool flag=true;
    char lastPressedKey = ' ';

    window.getEventManager().clearEvents();
    chrono::microseconds frameTime = chrono::microseconds::zero();
    while(flag){
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        drawBtns(window, btns);
        if(lastPressedKey==' ')
            lastPressedKey= getLastPressedChar(window);
        else if(btns[1].text.getContent().size()<15){
            btns[1].text.setContent(btns[1].text.getContent()+string(1,lastPressedKey));
            lastPressedKey = ' ';
            this_thread::sleep_for(chrono::milliseconds(160));
        }

        if(btns[1].text.getContent().size()>5){
            btns[2].rect.setFillColor(nsGraphics::KGreen);
            btns[2].buttonId = 2;
        }
        // On check si un bouton est cliqué
        int content = events(window.getEventManager(), btns);
        if(content==3){
            flag = false;
        }
        else if(content == 2){
            cout<<"Function to start the game"<<endl;
        }
        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

    }
}//startButton

/*!
  * @brief fonction acceder au menu qui affiche la liste des meilleurs scores
  * @param[in/out] window
  * @fn void scoreButton(MinGL &window)
**/
void scoreButton(MinGL &window){
    vector<string> leaderBoard(10);
    getLeaderBoard(leaderBoard);

    vector<button> btns(12);
    btns[0] = button {"Leaderboard :",0, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    for(unsigned i = 0 ; i<leaderBoard.size() ; ++i){
        btns[i+1] = button {leaderBoard[i],(int)i+1, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
    }
    btns[11] = button {"Back",11, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    placeBtns(window, btns);

    bool flag=true;
    window.getEventManager().clearEvents();
    chrono::microseconds frameTime = chrono::microseconds::zero();

    while(flag){
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        drawBtns(window, btns);

        // On check si un bouton est cliqué
        int content = events(window.getEventManager(), btns);
        if(content==11)
            flag=false;
        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

    }
}//scoreButton

/*!
  * @brief fonction utilisé pour acceder au menu des reglages
  * @param[in/out] window
  * @fn void settingsButton(MinGL &window)
**/
void settingsButton(MinGL &window){

    vector<button> btns(11);
    btns[0] = button {"To change a key : press the wanted key on the keyboard,",-1, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[1] = button {"then select the concearning button containing the key",-1, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[2] = button {"Left Move :",-1, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[3] = button {"q",3, nsGraphics::KWhite, nsGraphics::KGray, nsGraphics::KBlack};
    btns[4] = button {"Right Move :",-1, nsGraphics::KGray, nsGraphics::KGray, nsGraphics::KBlack};
    btns[5] = button {"d",5, nsGraphics::KWhite, nsGraphics::KGray, nsGraphics::KBlack};
    btns[6] = button {"Shoot :",-1, nsGraphics::KGray, nsGraphics::KGray, nsGraphics::KBlack};
    btns[7] = button {"z",7, nsGraphics::KWhite, nsGraphics::KGray, nsGraphics::KBlack};
    btns[8] = button {"Theme :",-1, nsGraphics::KGray, nsGraphics::KGray, nsGraphics::KBlack};
    btns[9] = button {"Windows vs Linux",9, nsGraphics::KWhite, nsGraphics::KGray, nsGraphics::KBlack};
    btns[10] = button {"Back",10, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    placeBtns(window, btns);

    map <int,string> themes;
    themes[0] = "Windows vs Linux";
    themes[1] = "Vanilla Space Invaders";
    int themeCounter = 0;

    bool flag=true;
    char lastPressedKey = ' ';

    window.getEventManager().clearEvents();
    chrono::microseconds frameTime = chrono::microseconds::zero();
    while(flag){
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();
        if(lastPressedKey==' ')
            lastPressedKey= getLastPressedChar(window);

        drawBtns(window, btns);

        // On check si un bouton est cliqué
        int content = events(window.getEventManager(), btns);

        if((content != 10 )&& (content != -1) && (content != 9 )){
            btns[content].text.setContent(string(1,lastPressedKey));
            lastPressedKey = ' ';
        }
        else if(content == 9){
            ++themeCounter;
            btns[content].text.setContent(themes[themeCounter%2]);
        }
        else if(content == 10){
            flag = false;
        }
        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

    }
}//settingsButton

/*!
  * @brief fonction qui sert à verifier quel bouton as été appuyé sur le menu principale, pour changer de fenetre
  * @param[in/out] window : fenetre
  * @param[in/out] content : contenu du bouton appuyé
  * @fn void checkContent(MinGL &window, int &content)
**/
void checkContent(MinGL &window, int &content){
    switch(content) {
    case -1:
        break;
    case 1://start
        startButton(window);
        break;
    case 2://score
        scoreButton(window);
        break;
    case 3://settings
        settingsButton(window);
        break;
    case 4://quit
        window.~MinGL();
        break;
    }
}//checkContent

void menu(){
    // Initialise le système
    const unsigned width = 1280;
    const unsigned heigth = 720;
    MinGL window("Space Invaders", nsGraphics::Vec2D(width, heigth), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    window.getEventManager().clearEvents();

    // Création des boutons
    vector<button> btns(4);
    btns[0] = button {"Start",1, nsGraphics::KBlue, nsGraphics::KRed, nsGraphics::KLime};
    btns[1] = button {"Scores",2, nsGraphics::KCyan, nsGraphics::KYellow, nsGraphics::KGreen};
    btns[2] = button {"Settings",3, nsGraphics::KTeal, nsGraphics::KMaroon, nsGraphics::KWhite};
    btns[3] = button {"Quit",4, nsGraphics::KGreen, nsGraphics::KMaroon, nsGraphics::KWhite};
    placeBtns(window, btns);

    int idbutton;
    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les boutons
        drawBtns(window, btns);

        // On check si un bouton est cliqué
        idbutton=events(window.getEventManager(), btns);
        checkContent(window, idbutton);

        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    window.getEventManager().clearEvents();
}
