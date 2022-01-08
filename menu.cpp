/*!
  * @author Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
  * @date 13 dec 2021
  * @brief fichier permettant de créer des menus pour commencer le jeu
**/

#include "menu.h"

using namespace std;


//nsGraphics::Vec2D rectPos;
//nsGraphics::RGBAcolor rectColor = nsGraphics::KCyan;

//struct boutons{
//    //texte a afficher et couleur dans laquelle l'afficher
//    string texte;
//    const::nsGraphics::RGBAcolor couleur;
//    int x_sup=0;
//    int y_sup=0;
//    int x_inf=0;
//    int y_inf=0;
//};


void events(nsEvent::EventManager &eventM, const vector<button> &btns)
{
    // On vérifie chaque évènement de la queue d'évènements
    while (eventM.hasEvent())
    {
        const nsEvent::Event_t event = eventM.pullEvent();

        // On regarde le type d'évènement
        nsEvent::MouseClickData_t data = event.eventData.clickData;
        nsGraphics::Vec2D eventPos{data.x, data.y};
        if(event.eventType==nsEvent::EventType_t::MouseClick && !data.button && !data.state){
            cout << endl << "A click : " << eventPos << endl;
            for(const button & btn : btns) {
                cout << btn.content << " at pos : " << btn.rect.getFirstPosition() << " | " << btn.rect.getSecondPosition() << endl;
                if (eventPos.isColliding(btn.rect.getFirstPosition(), btn.rect.getSecondPosition()))
                    cout << btn.content << endl;
            }
        }
    }
}//events


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
    nsGraphics::Vec2D btnSize{32*text_max_size, 64};

    for(size_t i=0; i<nb_btns; ++i) {

        nsGraphics::Vec2D pos1 = {winSize.getX()/2 - btnSize.getX()/2, i * winSize.getY()/nb_btns + winSize.getY()/(2*nb_btns) - btnSize.getY()/2};
        nsGraphics::Vec2D pos2 = pos1 + btnSize;
        nsGraphics::Vec2D textPos = pos1 + btnSize/2;

        btns[i].rect.setFirstPosition(pos1);
        btns[i].rect.setSecondPosition(pos2);
        btns[i].text.setPosition(textPos);

    }

}//placerBoutons

void drawBtns(MinGL &window, const vector<button> &btns) {
    for (const button &btn : btns)
        window << btn.rect << btn.text;
}

void menu()
{
    // Initialise le système
    const unsigned width = 600;
    const unsigned heigth = 600;
    MinGL window("Space Invaders", nsGraphics::Vec2D(width, heigth), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    window.getEventManager().clearEvents();

    // Création des boutons
    vector<button> btns(3);
    btns[0] = button {"Start", nsGraphics::KBlue, nsGraphics::KRed, nsGraphics::KLime};
    btns[1] = button {"Scores", nsGraphics::KCyan, nsGraphics::KYellow, nsGraphics::KGreen};
    btns[2] = button {"Quit", nsGraphics::KTeal, nsGraphics::KMaroon, nsGraphics::KOlive};
    placeBtns(window, btns);

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
        events(window.getEventManager(), btns);

        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    window.getEventManager().clearEvents();
}
