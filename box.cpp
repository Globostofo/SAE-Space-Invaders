/*!
 *
 * @file    box.cpp
 * @author  Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
 * @date    January 2022
 * @brief   Boxes Management
 *
 **/

#include "box.h"

bool nsBox::areColliding(const nsGraphics::Vec2D &position, const Box &box) {
    return box.firstPosition.getX() <= position.getX() <= box.secondPosition.getX()
            && box.firstPosition.getY() <= position.getY() <= box.secondPosition.getY();
} // areColliding

bool nsBox::areColliding(const Box &box1, const Box &box2) {
    nsGraphics::Vec2D b1c1 = box1.firstPosition;
    nsGraphics::Vec2D b1c2 = box1.secondPosition;
    nsGraphics::Vec2D b2c1 = box2.firstPosition;
    nsGraphics::Vec2D b2c2 = box2.secondPosition;

    return !(b1c2.getX() < b2c1.getX() || b2c2.getX() < b1c1.getX()
             || b1c2.getY() < b2c1.getY() || b2c2.getY() < b1c1.getY());
} // areColliding

void nsBox::clampInBox(nsGraphics::Vec2D &position, const Box &box) {
    position.setX(std::clamp(position.getX(),
                             box.firstPosition.getX(),
                             box.secondPosition.getX()));
    position.setY(std::clamp(position.getY(),
                             box.firstPosition.getY(),
                             box.secondPosition.getY()));
} // clampInBox
