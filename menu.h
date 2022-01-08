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
#include "mingl/gui/glut_font.h"
#include "mingl/gui/text.h"
#include "mingl/shape/line.h"
#include "mingl/event/event.hpp"

using namespace std;


//nsGraphics::Vec2D rectPos;
//nsGraphics::RGBAcolor rectColor = nsGraphics::KCyan;

struct button{
    //texte a afficher et couleur dans laquelle l'afficher

    string content;
    nsGraphics::RGBAcolor bgColor;
    nsGraphics::RGBAcolor borderColor;
    nsGraphics::RGBAcolor textColor;

    nsGui::Text text{nsGraphics::Vec2D{0,0},
                     content,
                     textColor,
                     nsGui::GlutFont::GlutFonts::BITMAP_9_BY_15,
                     nsGui::Text::ALIGNH_CENTER,
                     nsGui::Text::ALIGNV_CENTER};
    nsShape::Rectangle rect{nsGraphics::Vec2D{0,0},
                            nsGraphics::Vec2D{0,0},
                            bgColor,
                            borderColor};
};

void events(MinGL &window,vector<button> &b);

void placerBoutons(MinGL & window, vector<button> & b);

void menu();

#endif // MENU_H
