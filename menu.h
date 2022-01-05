#ifndef MENU_H
#define MENU_H


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

using namespace std;


//nsGraphics::Vec2D rectPos;
//nsGraphics::RGBAcolor rectColor = nsGraphics::KCyan;

struct boutons{
    //texte a afficher et couleur dans laquelle l'afficher
    string texte;
    const::nsGraphics::RGBAcolor couleur;
    int x_sup=0;
    int y_sup=0;
    int x_inf=0;
    int y_inf=0;
};


void events(MinGL &window,vector<boutons> &b);

void placerBoutons(MinGL & window, vector<boutons> & b,const unsigned & width, const unsigned & height);

void menu();

#endif // MENU_H
