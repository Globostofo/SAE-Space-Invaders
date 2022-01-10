#include "entity.h"

nsBox::Box nsEntity::getEntityBox(const Entity &entity) {
    nsGraphics::Vec2D spritePos = entity.sprite.getPosition();
    return nsBox::Box {spritePos, spritePos+entity.spriteSize};
}

void nsEntity::setEntitiesDirection(std::vector<Entity> &entities, const nsGraphics::Vec2D &direction) {
    for (Entity &entity : entities)
        entity.direction = direction;
}

void nsEntity::dispEntities(MinGL &window, const Entity &entity) {
    window << entity.sprite;
}

void nsEntity::dispEntities(MinGL &window, const std::vector<Entity> &entityVec) {
    for (const Entity &entity : entityVec)
        dispEntities(window, entity);
}

bool nsEntity::isOutOfBounds(const Entity &entity) {
    return entity.canGoOutOfBounds && !nsBox::areColliding(entity.bounds, getEntityBox(entity));
}

void nsEntity::moveEntities(Entity &entity) {
    nsGraphics::Vec2D newPos = entity.sprite.getPosition() + entity.direction.toSize(entity.speed);
    if (!entity.canGoOutOfBounds)
        nsBox::clampInBox(newPos, entity.bounds);
    entity.sprite.setPosition(newPos);
}

void nsEntity::moveEntities(std::vector<Entity> &entityVec) {
    for (Entity &entity : entityVec)
        moveEntities(entity);
}

void nsEntity::entitiesCollisions(Entity &entity1, Entity &entity2) {
    if (nsBox::areColliding(getEntityBox(entity1), getEntityBox(entity2))) {
        const std::vector<EntityType> whoHurts1 = entitiesCollider.find(entity1.type)->second;
        const std::vector<EntityType> whoHurts2 = entitiesCollider.find(entity2.type)->second;
        if (find(whoHurts1.begin(), whoHurts1.end(), entity2.type) != whoHurts1.end()) {
            entity1.lifePoints -= 1;
        }
        if (find(whoHurts2.begin(), whoHurts2.end(), entity1.type) != whoHurts2.end()) {
            entity2.lifePoints -= 1;
        }
    }
}

void nsEntity::entitiesCollisions(Entity &entity1, std::vector<Entity> &entityVec2) {
    for (Entity &entity2: entityVec2)
        entitiesCollisions(entity1, entity2);
}

void nsEntity::entitiesCollisions(std::vector<Entity> &entityVec1,
                        std::vector<Entity> &entityVec2) {
    for (Entity &entity1 : entityVec1) for (Entity &entity2 : entityVec2)
        entitiesCollisions(entity1, entity2);
}

void nsEntity::deleteDiedEntities(std::vector<Entity> &entities) {
    for (std::vector<Entity>::iterator it=entities.begin(); it<entities.end(); ++it)
        if ((*it).lifePoints <= 0 || ((*it).canGoOutOfBounds && isOutOfBounds(*it)))
            entities.erase(it);
}
