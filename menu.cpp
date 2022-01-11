#include "menu.h"

using namespace std;

int nsMenu::events(nsEvent::EventManager &eventM, const vector<Button> &btns) {
    // On vérifie chaque évènement de la queue d'évènements
    while (eventM.hasEvent())
    {
        const nsEvent::Event_t event = eventM.pullEvent();

        // On regarde le type d'évènement
        nsEvent::MouseClickData_t data = event.eventData.clickData;
        nsGraphics::Vec2D eventPos{data.x, data.y};
        if(event.eventType==nsEvent::EventType_t::MouseClick && !data.button && !data.state){
            //cout << endl << "A click : " << eventPos << endl;
            for(const Button & btn : btns) {
                //cout << btn.content << " at pos : " << btn.rect.getFirstPosition() << " | " << btn.rect.getSecondPosition() << endl;
                if (eventPos.isColliding(btn.rect.getFirstPosition(), btn.rect.getSecondPosition())){
                    //cout << btn.content << endl;
                    return btn.buttonId;
                }
            }
        }
    }
    return -1;
} // events()

char nsMenu::getLastPressedChar(MinGL &window) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(auto letter : alphabet){
        if (window.isPressed({letter, false})){
            //cout<<letter<<endl;
            return letter;
        }
    }
    return ' ';
} // getLastPressedChar()

void nsMenu::placeBtns(const MinGL &window, vector<Button> &btns) {

    nsGraphics::Vec2D winSize = window.getWindowSize();
    size_t nb_btns = btns.size();

    unsigned text_max_size = 0;
    for (const Button &btn : btns)
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

} // placeBtns()

void nsMenu::drawBtns(MinGL &window, const vector<Button> &btns) {
    for (const Button &btn : btns)
        window << btn.rect << btn.text;
} // drawBtns()

void nsMenu::getLeaderBoard(vector<string> &leaderBoard){
    //leaderBoard init to 10
    string score;
    ifstream scoreFile ("leaderBoard.txt");
    for(vector<string>::iterator iter = leaderBoard.begin(); iter !=leaderBoard.end(); ++iter){
        getline(scoreFile,score);
        (*iter)=score;
    }
} // getLeaderBoard()

void nsMenu::readFile(map<unsigned,string> &fileOutPut, string filename){

    ifstream file (filename);
    string line;

    while(getline(file,line)){

        string value="";
        string key="";
        bool isSeparatorfound = false;

        for(char letter : line){
            if(letter == ':'){
                isSeparatorfound = true;
                continue;
            }
            if(isSeparatorfound){
                value+=string(1,letter);
            }
            else{
                key+=string(1,letter);
            }
        }
        fileOutPut[stoul(key)]=value;
    }
}// readFile

void nsMenu::readConfFile(map<string,string> &settings) {

    ifstream configFile ("config.yaml");
    string line;

    while(getline(configFile,line)){

        string value="";
        string key="";
        bool isSeparatorfound = false;

        for(char letter : line){
            if(letter == ':'){
                isSeparatorfound = true;
                continue;
            }
            if(isSeparatorfound){
                value+=string(1,letter);
            }
            else{
                key+=string(1,letter);
            }
        }
        settings[key]=value;
    }
} // readConfFile()

void nsMenu::writeConfigFile(map<string,string> &settings) {

    ofstream ofs ("config.yaml");
    for(map<string,string>::iterator iter = settings.begin(); iter!=settings.end(); ++iter){
        ofs<<(*iter).first<<":"<<(*iter).second<<endl;
    }
    ofs.close();
} // writeConfigFile()

void nsMenu::startButton(MinGL &window) {
    //initialisation des boutons du menu Start
    vector<Button> btns(5);
    btns[0] = Button {"Enter your Name :",0, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[1] = Button {" ",1, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[2] = Button {"Delete last character",2, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[3] = Button {"Play",-1, nsGraphics::KRed, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[4] = Button {"Back",4, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    placeBtns(window, btns);

    //variables
    bool flag=true;
    char lastPressedKey = ' ';

    //Re initialiser les valeurs de la fenetre necessaires
    window.getEventManager().clearEvents();
    chrono::microseconds frameTime = chrono::microseconds::zero();

    while(flag) {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        //dessiner boutons
        drawBtns(window, btns);

        //recuperer la derniere valeur inseré au clavier par l'utilisateur
        if(lastPressedKey==' ')
            lastPressedKey= getLastPressedChar(window);
        else if(btns[1].text.getContent().size()<15){
            btns[1].text.setContent(btns[1].text.getContent()+string(1,lastPressedKey));
            lastPressedKey = ' ';
            this_thread::sleep_for(chrono::milliseconds(140));
        }

        //Verifier si l'utilisateur peut appuyer sur le bouton pour commencer, conditions : un username de 5 caracteres
        if(btns[1].text.getContent().size()>5){
            btns[3].rect.setFillColor(nsGraphics::KGreen);
            btns[3].buttonId = 3;
        }
        else{
            btns[3].rect.setFillColor(nsGraphics::KRed);
            btns[3].buttonId = -1;
        }

        // On check si un bouton est cliqué
        int content = events(window.getEventManager(), btns);

        if(content==4){//revenir en arriere
            flag = false;
        }
        else if(content == 2 && btns[1].text.getContent().size()>0){//effacer la derniere lettre dans le bouton username
            string username = btns[1].text.getContent();
            username.erase(prev(username.end()));
            btns[1].text.setContent(username);
        }
        else if(content == 3){//commencer la partie
            cout<<"Function to start the game"<<endl;
        }

        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

    }
} // startButton()

void nsMenu::scoreButton(MinGL &window){
    
    map<unsigned,string> leaderBoard;
    readFile(leaderBoard,"leaderBoard.txt");

    vector<Button> btns(12);
    btns[0] = Button {"Leaderboard :",0, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    unsigned i =0;
    for(map<unsigned,string>::reverse_iterator iter = leaderBoard.rbegin(); iter!=leaderBoard.rend(); ++iter){
        btns[i+1] = button {(*iter).second+":"+to_string((*iter).first),(int)i+1, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
        ++i;
    }
    btns[11] = Button {"Back",11, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
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
} // scoreButton()

void nsMenu::settingsButton(MinGL &window){

    //Dictionary containing the configs from the config file
    map<string,string> settings;
    readConfFile(settings);

    //Dictionary containing the differents themes avaible
    map <int,string> themes;
    themes[0] = "Windows vs Linux";
    themes[1] = "Vanilla Space Invaders";
    int themeCounter = 0;

    //Dictionary containing the keys of the config file on the second value, and on first value their buttonId
    map<int,string> buttonContent;
    buttonContent[3]="LeftKey";
    buttonContent[5]="RightKey";
    buttonContent[7]="ShootKey";
    buttonContent[9]="Theme";

    //Init the button list
    vector<Button> btns(11);
    btns[0] = Button {"To change a key : press the wanted key on the keyboard,",-1, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[1] = Button {"then select the concearning button containing the key",-1, nsGraphics::KSilver, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[2] = Button {"Left Key :",-1, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
    btns[3] = Button {settings["LeftKey"],3, nsGraphics::KWhite, nsGraphics::KGray, nsGraphics::KBlack};
    btns[4] = Button {"Right Key :",-1, nsGraphics::KGray, nsGraphics::KGray, nsGraphics::KBlack};
    btns[5] = Button {settings["RightKey"],5, nsGraphics::KWhite, nsGraphics::KGray, nsGraphics::KBlack};
    btns[6] = Button {"Shoot Key :",-1, nsGraphics::KGray, nsGraphics::KGray, nsGraphics::KBlack};
    btns[7] = Button {settings["ShootKey"],7, nsGraphics::KWhite, nsGraphics::KGray, nsGraphics::KBlack};
    btns[8] = Button {"Theme :",-1, nsGraphics::KGray, nsGraphics::KGray, nsGraphics::KBlack};
    btns[9] = Button {themes[stoi( settings["Theme"] )],9, nsGraphics::KWhite, nsGraphics::KGray, nsGraphics::KBlack};
    btns[10] = Button {"Back",10, nsGraphics::KGray, nsGraphics::KWhite, nsGraphics::KBlack};
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

        //On recupere la derniere lettre appuyé
        if(lastPressedKey==' ')
            lastPressedKey= getLastPressedChar(window);

        //On dessine les buttons
        drawBtns(window, btns);

        // On check si un bouton est cliqué
        int content = events(window.getEventManager(), btns);

        if((content != 10 )&& (content != -1) && (content != 9 )){  //Changer les touches
            string lastPressedKeyString=string(1,lastPressedKey);   //impossible to affect the value to the map without passing through another variable

            btns[content].text.setContent(lastPressedKeyString);
            lastPressedKey = ' ';

            settings[buttonContent[content]]=lastPressedKeyString;

        }
        else if(content == 9){                                      //changer le theme
            ++themeCounter;
            btns[content].text.setContent(themes[themeCounter%2]);

            int themeCounterAfterModule = themeCounter%2;           //impossible to affect the value to the map without passing through another variable
            string theme = to_string(themeCounterAfterModule);      //impossible to affect the value to the map without passing through another variable
            settings[buttonContent[content]]=theme;
        }
        else if(content == 10){                                     // revenir en arriere
            flag = false;
        }
        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    writeConfigFile(settings);
} // settingsButton()

void nsMenu::checkContent(MinGL &window, int &content){
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
} // checkContent()

void nsMenu::menu() {
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
    vector<Button> btns(4);
    btns[0] = Button {"Start",1, nsGraphics::KBlue, nsGraphics::KRed, nsGraphics::KLime};
    btns[1] = Button {"Scores",2, nsGraphics::KCyan, nsGraphics::KYellow, nsGraphics::KGreen};
    btns[2] = Button {"Settings",3, nsGraphics::KTeal, nsGraphics::KMaroon, nsGraphics::KWhite};
    btns[3] = Button {"Quit",4, nsGraphics::KGreen, nsGraphics::KMaroon, nsGraphics::KWhite};
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
} // menu()
