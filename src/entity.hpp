#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "coordinate.h"

class Entity 
{

public:
    Entity(int id = -1, Coordinate coordinate = {-1,-1});

    virtual ~Entity() = default;

    virtual int getId() const;
    virtual Coordinate getCoordinate() const;

protected:
    int id_;
    Coordinate coordinate_;
};


#endif
