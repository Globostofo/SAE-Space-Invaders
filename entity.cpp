#include "entity.h"

nsBox::Box nsEntity::getEntityBox(const Entity &entity) {
    nsGraphics::Vec2D spritePos = entity.sprite.getPosition();
    return nsBox::Box {spritePos, spritePos+entity.spriteSize};
}

void nsEntity::setEntitiesDirection(std::vector<Entity> &entities, const nsGraphics::Vec2D &direction, const EntityType &type) {
    for (Entity &entity : entities)
        if (entity.type == type)
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

void nsEntity::moveEntities(std::vector<Entity> &entityVec, const EntityType &type) {
    for (Entity &entity : entityVec)
        if (entity.type == type)
            moveEntities(entity);
}

void nsEntity::entitiesCollisions(Entity &entity1, Entity &entity2, unsigned &score) {
    if (nsBox::areColliding(getEntityBox(entity1), getEntityBox(entity2))) {
        const std::vector<EntityType> whoHurts1 = entitiesCollider.find(entity1.type)->second;
        const std::vector<EntityType> whoHurts2 = entitiesCollider.find(entity2.type)->second;
        if (find(whoHurts1.begin(), whoHurts1.end(), entity2.type) != whoHurts1.end()) {
            // Adding score on invader hit
            if (entity1.type == INVADER) score += nsConsts::invaderHurt;
            entity1.lifePoints -= 1;
        }
        if (find(whoHurts2.begin(), whoHurts2.end(), entity1.type) != whoHurts2.end()) {
            if (entity2.type == INVADER) score += nsConsts::invaderHurt;
            entity2.lifePoints -= 1;
        }
    }
}

void nsEntity::entitiesCollisions(std::vector<Entity> &entityVec, unsigned &score) {
    auto it1 = entityVec.begin();
    auto it2 = entityVec.begin()+1;
    do {
        entitiesCollisions(*it1, *it2, score);
        if (it2 == entityVec.end()-1)
            it2 = it1++;
        else
            ++it2;
    } while (it1 != entityVec.end()-2);
}

void nsEntity::deleteDiedEntities(std::vector<Entity> &entities, unsigned &score) {
    for (std::vector<Entity>::iterator it=entities.begin(); it<entities.end(); ++it)
        if ((*it).lifePoints <= 0 || ((*it).canGoOutOfBounds && isOutOfBounds(*it))) {

            // Adding score on invader death
            if ((*it).type == INVADER) {
                score += nsConsts::invaderDeath;
            }

            entities.erase(it);
        }
}
