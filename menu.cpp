/*!
  * @author Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
  * @date 13 dec 2021
  * @brief fichier permettant de créer des menus pour commencer le jeu
**/

#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/shape/rectangle.h"
#include "mingl/mingl.h"
#include "mingl/gui/text.h"
#include "mingl/shape/line.h"
#include "mingl/event/event.hpp"
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


void events(MinGL &window,vector<boutons> &b)
{
    // On vérifie chaque évènement de la queue d'évènements
    while (window.getEventManager().hasEvent())
    {
        const nsEvent::Event_t actualEvent = window.getEventManager().pullEvent();

        // On regarde le type d'évènement

        if(actualEvent.eventType==nsEvent::EventType_t::MouseClick){
            for(const boutons & bouton : b){

                if((actualEvent.eventData.clickData.x>bouton.x_sup)
                        &&(actualEvent.eventData.clickData.x<bouton.x_inf)
                        &&(actualEvent.eventData.clickData.y>bouton.y_sup)
                        &&(actualEvent.eventData.clickData.y<bouton.y_inf)){

                    cout<<"Hello"<<endl;
                }
            }
        }
    }
}//events


/*!
  * @brief fonction pour placer des boutons centrés horizontalement et verticalement
  * @param[in out] window : fenetre
  * @param[in] b : vecteur de struct contenant le texte à afficher et la couleur dans laquelle l'afficher
  * @param[in] width : largeur de la fenetre
  * @param[in] height : hauteur de la fenetre
**/
void placerBoutons(MinGL & window, vector<boutons> & b,const unsigned & width, const unsigned & height)
{
    for(size_t i = 0; i < b.size(); ++i)
    {



        const unsigned x_texte=(width/2)-((unsigned((b[i].texte).size()))*4.5);
        const unsigned y_texte=(height/(unsigned (b.size())+1))*unsigned(i+1);

        const unsigned marge_x = 100;//constantes
        const unsigned marge_y = 30;

        b[i].x_sup = x_texte-marge_x;
        b[i].y_sup = y_texte-marge_y;
        b[i].x_inf = x_texte+(unsigned((b[i].texte).size()))*9+marge_x;
        b[i].y_inf = y_texte+(unsigned((b[i].texte).size()))+marge_y;

        window << nsShape::Rectangle(nsGraphics::Vec2D(b[i].x_sup,b[i].y_sup),
                                     nsGraphics::Vec2D(b[i].x_inf,b[i].y_inf),
                                     nsGraphics::KTransparent,b[i].couleur);

        window << nsGui::Text(nsGraphics::Vec2D(x_texte,y_texte),b[i].texte,b[i].couleur, nsGui::GlutFont::BITMAP_HELVETICA_18);
    }
}//placerBoutons


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

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine le texte
        //constante qui stocke la taille de la police



        boutons b {"Start", nsGraphics::KRed};
        boutons b2 {"Scores", nsGraphics::KWhite};
        boutons b3 {"Quit", nsGraphics::KCyan};
        vector <boutons> v;
        v.push_back(b);
        v.push_back(b2);
        v.push_back(b3);

        placerBoutons(window,v,width,heigth);

        events(window,v);



        // On finit la frame en cours
        window.finishFrame();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    window.getEventManager().clearEvents();
}
