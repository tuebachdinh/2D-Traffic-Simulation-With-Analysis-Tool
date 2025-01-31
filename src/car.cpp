#include "car.hpp"
#include "road.hpp"
#include "building.hpp"
#include "city.hpp"
#include "global.h"
#include <iostream>
#include <memory>
#include <cmath>

/**
 * @class Car
 * @brief Represents a car in the simulation.
 *
 * The `Car` class simulates a car's behavior, including movement, direction, and interactions with roads 
 * and intersections. It supports functionality to control the car's position, speed, and state while driving 
 * towards a destination. The class handles transitions between roads and intersections, updates car position 
 * based on its speed, and allows interaction with other cars.
 */


/**
 * @brief Constructs a Car object with a unique id.
 * 
 * @param id The unique id of the car.
 */
Car::Car(int id) {
    id_ = id;
}

/**
 * @brief Constructs a Car object with a unique id, spawn building, and speed.
 * 
 * @param id The unique id of the car.
 * @param spawnBuilding A shared pointer to the building where the car spawns.
 * @param speed The speed at which the car moves.
 */
Car::Car(int id, std::shared_ptr<Building> spawnBuilding, float speed) {
    id_ = id;
    speed_ = speed;
    coordinate_ = spawnBuilding->getAdjacentCell();
    currentRoad_ = spawnBuilding->getAdjacentRoad();
    direction_ = currentRoad_->getDirection1();
}

/**
 * @brief Gets the speed of the car.
 * 
 * @return The speed of the car.
 */
float Car::getSpeed() const { return speed_; }

/**
 * @brief Gets the current road the car is traveling on.
 * 
 * @return A shared pointer to the current road.
 */
std::shared_ptr<Road> Car::getCurrentRoad() { return currentRoad_; }

/**
 * @brief Gets the direction the car is moving in.
 * 
 * @return The direction the car is facing.
 */
Direction Car::getDirection() const { return direction_; }

/**
 * @brief Sets the position of the car to a new coordinate.
 * 
 * @param newPosition The new coordinate for the car.
 */
void Car::setPosition(Coordinate newPosition) { coordinate_ = newPosition; }

/**
 * @brief Sets the direction of the car to a new direction.
 * 
 * @param newDirection The new direction the car is facing.
 */
void Car::setDirection(Direction newDirection) { direction_ = newDirection; }

/**
 * @brief Sets the car that is in front of the current car.
 * 
 * @param car A shared pointer to the car in front.
 */
void Car::setCarInfront(std::shared_ptr<Car> car) { carInfront_ = car; }

/**
 * @brief Drives the car towards a destination.
 * 
 * This method moves the car along its current road or intersection towards the
 * given destination. It handles road and intersection transitions and determines
 * the new position and direction of the car.
 * 
 * @param dest The destination coordinate the car is trying to reach.
 * 
 * @return true if the car reached the destination, false otherwise.
 */
bool Car::drive(Coordinate dest) {
    double dx = dest.x - coordinate_.x;
    double dy = dest.y - coordinate_.y;
    double distance = std::sqrt(dx * dx + dy * dy);
    if (distance <= 0.21) return true;

    // If the car is currently on a road, continue driving along it.
    if (currentRoad_) {
        if (direction_ == North) coordinate_.y -= speed_;
        else if (direction_ == South) coordinate_.y += speed_;
        else if (direction_ == East) coordinate_.x += speed_;
        else if (direction_ == West) coordinate_.x -= speed_;
        
        // If the car reaches either end of the road, remove it from the road and reset road.
        if (coordinate_ == currentRoad_->getFrom()->getCoordinate()) {
            currentIntersection_ = currentRoad_->getFrom();
            currentRoad_->removeCar(std::make_shared<Car>(*this));
            currentRoad_ = nullptr;
        } else if (coordinate_ == currentRoad_->getEnd()->getCoordinate()) {
            currentIntersection_ = currentRoad_->getEnd();
            currentRoad_->removeCar(std::make_shared<Car>(*this));
            currentRoad_ = nullptr;
        }
    } else if (currentIntersection_) {
        auto dx = dest.x - coordinate_.x;
        auto dy = dest.y - coordinate_.y;
        std::shared_ptr<Road> futureRoad = nullptr;
        carInfront_ = nullptr;

        // Determine possible directions based on the car's movement.
        std::vector<Direction> directions;
        if (std::abs(dx) > std::abs(dy)) {
            directions = {
                dx > 0 ? East : West,
                dy > 0 ? North : South,
                dy > 0 ? South : North,
                dx > 0 ? West : East
            };
        } else {
            directions = {
                dy > 0 ? South : North,
                dx > 0 ? East : West,
                dx > 0 ? West : East,
                dy > 0 ? North : South
            };
        }

        // Try to move the car to the next valid road.
        for (const auto& direction : directions) {
            if (futureRoad) break;
            if (!direction == direction_) continue;  // Skip if the direction is not the intended one.
            futureRoad = currentIntersection_->getRoad(direction);
            if (futureRoad) {
                futureRoad->addCar(std::make_shared<Car>(*this), direction);
                currentRoad_ = futureRoad;
                direction_ = direction;
                currentIntersection_ = nullptr;
            }
        }
    }
    return false;
}