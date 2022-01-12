#include <map>

#include "box.h"
#include "consts.h"

#include "MinGL2/include/mingl/graphics/vec2d.h"
#include "MinGL2/include/mingl/gui/sprite.h"

namespace nsEntity {

/*!
 * @enum EntityType
 * @brief Enum used to know what is the type of entity (usefull for collisions)
 */
enum EntityType {
    SHIP,
    SHIP_BULLET,
    SHIELD,
    INVADER,
    INVADER_BULLET
}; // enum EntityType

/*!
 * @brief Map used to know which type of entities can be hurted by which types
 */
const std::map<EntityType, std::vector<EntityType>> entitiesCollider {
    {SHIP,           {INVADER, INVADER_BULLET}},
    {SHIP_BULLET,    {SHIELD, INVADER, INVADER_BULLET}},
    {SHIELD,         {SHIP_BULLET, INVADER, INVADER_BULLET}},
    {INVADER,        {SHIP_BULLET}},
    {INVADER_BULLET, {SHIP, SHIP_BULLET, SHIELD}}
}; // map entitiesCollider

/*!
 * @struct Entity
 * @brief Struct used to manage any object in game like player, bullets, shields...
 */
struct Entity {
    EntityType type;
    nsGui::Sprite sprite;
    nsGraphics::Vec2D spriteSize;
    int lifePoints;
    nsBox::Box bounds;
    int speed = 10;
    nsGraphics::Vec2D direction = nsGraphics::Vec2D();
    bool canGoOutOfBounds = false;
}; // struct Entity

/*!
 * @brief Get the box of the given entity depending of its position and size
 * @param[in] entity : object we want to get box
 * @fn nsBox::Box getEntityBox(const Entity &entity);
 */
nsBox::Box getEntityBox(const Entity &entity);

/*!
 * @brief Procedure with just a loop to change direction of entities in vector
 * @param[in/out] entities : objects we want to change direction
 * @param[in] direction : new direction
 * @fn void setEntitiesDirection(std::vector<Entity> &entities, const nsGraphics::Vec2D &direction);
 */
void setEntitiesDirection(std::vector<Entity> &entities, const nsGraphics::Vec2D &direction, const EntityType &type);

/*!
 * @brief Procedure used to put an entity on window
 * @param[in/out] window : where we want to display the entity
 * @param[in] entity : object to display
 * @fn void dispEntities(MinGL &window, const Entity &entity);
 */
void dispEntities(MinGL &window, const Entity &entity);

/*!
 * @brief Procedure used to put many entities on window
 * @param[in/out] window : where we want to display the entities
 * @param[in] entityVec : vector of object to display
 * @fn void dispEntities(MinGL &window, const std::vector<Entity> &entityVec);
 */
void dispEntities(MinGL &window, const std::vector<Entity> &entityVec);

/*!
 * @brief Predicate use to know if an entity is completely exited its bounds
 * @param[in] entity : entity to check
 * @fn bool isOutOfBounds(const Entity &entity);
 */
bool isOutOfBounds(const Entity &entity);

/*!
 * @brief Procedure used to move an entity according to its speed and direction
 * @param[in/out] entity : entity to move
 * @fn void moveEntities(Entity &entity);
 */
void moveEntities(Entity &entity);

/*!
 * @brief Procedure with just a loop to move all entities in the vector
 * @param[in/out] entityVec : entities to move
 * @fn void moveEntities(std::vector<Entity> &entityVec);
 */
void moveEntities(std::vector<Entity> &entityVec, const EntityType &type);

/*!
 * @brief Procedure to check collisions between two entities according to their collisions mask (map entitiesCollider)
 * @param[in/out] entity1 : first entity to check
 * @param[in/out] entity2 : second entity to check
 * @fn void entitiesCollisions(Entity &entity1, Entity &entity2);
 */
void entitiesCollisions(Entity &entity1, Entity &entity2, unsigned &score);

/*!
 * @brief Procedure with just two loops to making collides each entity from first vector to each entity from second vector
 * @param[in/out] entityVec1 : first vector to check
 * @param[in/out] entityVec2 : second vector to check
 * @fn void entitiesCollisions(std::vector<Entity> &entityVec1, std::vector<Entity> &entityVec2);
 */
void entitiesCollisions(std::vector<Entity> &entityVec, unsigned &score);

/*!
 * @brief Procedure to remove entities from vector if its number of lifes is under 0 or if it's out of bounds
 * @param[in/out] entities : vector to check
 * @fn void deleteDiedEntities(std::vector<Entity> &entities);
 */
void deleteDiedEntities(std::vector<Entity> &entities, unsigned &score);

} // namespace nsEntity
