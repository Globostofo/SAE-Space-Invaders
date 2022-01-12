#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>

#include "mingl/event/event_manager.h"
#include "mingl/gui/text.h"
#include "mingl/shape/rectangle.h"

#include "consts.h"

namespace nsButton {

/*!
  * @struct structure contenant l'element button
  * @fn button{std::string content, int buttonId,  nsGraphics::RGBAcolor bgColor,  nsGraphics::RGBAcolor borderColor,  nsGraphics::RGBAcolor textColor }
**/
struct Button {
    std::string content;    // just used for initialization

    nsGui::Text text = nsGui::Text(nsGraphics::Vec2D(),
                                   content,
                                   nsConsts::textColor,
                                   nsConsts::textFont,
                                   nsGui::Text::ALIGNH_CENTER,
                                   nsGui::Text::ALIGNV_CENTER);
    nsShape::Rectangle rect = nsShape::Rectangle(nsGraphics::Vec2D(),
                                                 nsGraphics::Vec2D(9*content.size()+64, 64),
                                                 nsConsts::btBgColor,
                                                 nsConsts::btBorderColor);
}; // struct Button

/*!
  * @brief fonction pour verifier si on appuye sur la fenetre de jeu et si un bouton est concerné
  * @param[in/out] EventManager
  * @param[in] btns : vecteur contenant les boutons
  * @fn int events(nsEvent::EventManager &eventM, const std::vector<button> &btns)
**/
bool isPressed(nsEvent::EventManager &eventM, const Button &bt);

nsGraphics::Vec2D getSize(const Button &bt);

void setPosition(Button &bt, const nsGraphics::Vec2D &position);

/*!
  * @brief fonction pour placer des boutons centrés horizontalement et verticalement
  * @param[in/out] window : fenetre
  * @param[in] b : vecteur de struct contenant le texte à afficher et la couleur dans laquelle l'afficher
  * @param[in] width : largeur de la fenetre
  * @param[in] height : hauteur de la fenetre
**/
void placeBtns(std::vector<Button> &btns);

/*!
  * @brief fonction utilisé pour afficher les boutons dans la fenetre : window
  * @param[in/out] window
  * @param[in] btns : vecteur contenant la liste des boutons à afficher
  * @fn void drawBtns(MinGL &window, const std::vector<button> &btns)
**/
void drawBtns(MinGL &window, const std::vector<Button> &btns);

}

#endif // BUTTON_H
