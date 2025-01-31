#ifndef ENTITY_CPP
#define ENTITY_CPP

#include "entity.hpp"

/**
 * @class Entity
 * @brief Represents an entity with a unique id and a coordinate.
 *
 * This class stores information about an entity, including its unique ID
 * and its coordinate. It provides getter methods to access these values.
 */
Entity::Entity(int id, Coordinate coordinate): id_(id), coordinate_(coordinate){}

/**
 * @brief Gets the coordinate of the entity.
 * @return The coordinate of the entity as a `Coordinate` object.
 */
Coordinate Entity::getCoordinate() const { return coordinate_; }


/**
 * @brief Gets the ID of the entity.
 * @return The ID of the entity as an integer.
 */
int Entity::getId() const { return id_; }

#endif