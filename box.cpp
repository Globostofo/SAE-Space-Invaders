#include "box.h"

/*!
 * @brief Permit to check if the given point is inside given box
 * @param[in] position : point position
 * @param[in] box : rectangle to check
 * @fn bool areColliding(const nsGraphics::Vec2D &position, const Box &box);
 */
bool nsBox::areColliding(const nsGraphics::Vec2D &position, const Box &box) {
    return box.firstPosition.getX() <= position.getX() <= box.secondPosition.getX()
            && box.firstPosition.getY() <= position.getY() <= box.secondPosition.getY();
} // areColliding

/*!
 * @brief Permit to check if two boxes are colliding
 * @param[in] box1 : first box
 * @param[in] box2 : second box
 * @fn bool areColliding(const Box &box1, const Box &box2);
 */
bool nsBox::areColliding(const Box &box1, const Box &box2) {
    nsGraphics::Vec2D b1c1 = box1.firstPosition;
    nsGraphics::Vec2D b1c2 = box1.secondPosition;
    nsGraphics::Vec2D b2c1 = box2.firstPosition;
    nsGraphics::Vec2D b2c2 = box2.secondPosition;

    return !(b1c2.getX() < b2c1.getX() || b2c2.getX() < b1c1.getX()
             || b1c2.getY() < b2c1.getY() || b2c2.getY() < b1c1.getY());
} // areColliding

/*!
 * @brief Move a position to the nearest point in the box
 * @param[in/out] position : position to clamp
 * @param[in] box : given limits
 * @fn void clampInBox(nsGraphics::Vec2D &position, const Box &box);
 */
void nsBox::clampInBox(nsGraphics::Vec2D &position, const Box &box) {
    position.setX(std::clamp(position.getX(),
                             box.firstPosition.getX(),
                             box.secondPosition.getX()));
    position.setY(std::clamp(position.getY(),
                             box.firstPosition.getY(),
                             box.secondPosition.getY()));
} // clampInBox
