/*!
 *
 * @file    button.h
 * @author  Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
 * @date    January 2022
 * @brief   Buttons Management
 *
 **/

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
  * @struct struct containing the button element
  * @brief struct button : place and center the text in content, into a Rectangle
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
  * @brief function used to verify if a button is pressed
  * @param[in/out] EventManager
  * @param[in] btn : button
  * @fn bool isPressed(nsEvent::EventManager &eventM, const Button &bt)
**/
bool isPressed(nsEvent::EventManager &eventM, const Button &bt);

/*!
  * @brief procedure used to move the position of a button
  * @param[in/out] EventManager
  * @param[in] btns : list containing the buttons
  * @fn int events(nsEvent::EventManager &eventM, const std::vector<button> &btns)
**/
void setPosition(Button &bt, const nsGraphics::Vec2D &position);

/*!
  * @brief procedure used to place des buttons aligned horizontally and vertically
  * @param[in] btns : list containing the buttons
  * @fn void placeBtns(std::vector<Button> &btns)
**/
void placeBtns(std::vector<Button> &btns);

/*!
  * @brief procedure used to draw the buttons on the window
  * @param[in/out] window
  * @param[in] btns : list containing the buttons to draw
  * @fn void drawBtns(MinGL &window, const std::vector<button> &btns)
**/
void drawBtns(MinGL &window, const std::vector<Button> &btns);

}// namespace nsButton

#endif // BUTTON_H
