#ifndef BOX_H
#define BOX_H

#include <algorithm>

#include "MinGL2/include/mingl/graphics/vec2d.h"

namespace nsBox {

/*!
 * @struct Box
 * @brief Rectangle made with two points (corners) to manage collisions
 */
struct Box {
    nsGraphics::Vec2D firstPosition;
    nsGraphics::Vec2D secondPosition;
}; // struct Box

/*!
 * @brief Permit to check if the given point is inside given box
 * @param[in] position : point position
 * @param[in] box : rectangle to check
 * @fn bool areColliding(const nsGraphics::Vec2D &position, const Box &box);
 */
bool areColliding(const nsGraphics::Vec2D &position, const Box &box);

/*!
 * @brief Permit to check if two boxes are colliding
 * @param[in] box1 : first box
 * @param[in] box2 : second box
 * @fn bool areColliding(const Box &box1, const Box &box2);
 */
bool areColliding(const Box &box1, const Box &box2);

/*!
 * @brief Move a position to the nearest point in the box
 * @param[in/out] position : position to clamp
 * @param[in] box : given limits
 * @fn void clampInBox(nsGraphics::Vec2D &position, const Box &box);
 */
void clampInBox(nsGraphics::Vec2D &position, const Box &box);

} // namespace nsBox

#endif // BOX_H
