#ifndef CAR_HPP
#define CAR_HPP

#include <string>
#include <utility>
#include <cmath>
#include "coordinate.h"
#include "road.hpp"
#include "building.hpp"
#include "intersection.hpp"
#include "direction_enum.h"
#include "entity.hpp"

class Building;

class Car : public Entity { 
    
public:
    Car(int id);
    Car(int id, std::shared_ptr<Building> spawnBuilding, float speed = 0.1f);
    float getSpeed() const;
    std::shared_ptr<Road> getCurrentRoad();
    Direction getDirection() const;
    void setPosition(Coordinate newPosition);
    void setDirection(Direction newDirection);
    void setCarInfront(std::shared_ptr<Car> car);
    bool drive(Coordinate dest);
    
private:
    float speed_;                      
    std::shared_ptr<Road> currentRoad_;
    std::shared_ptr<Intersection> currentIntersection_ = nullptr;
    std::shared_ptr<Car> carInfront_ = nullptr;
    Direction direction_;           
};

#endif 

