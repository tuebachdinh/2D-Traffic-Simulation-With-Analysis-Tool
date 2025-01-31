#include "bus.hpp"
#include <iostream>

/**
 * @class Bus
 * @brief Represents a bus in the simulation that follows a route with multiple stops.
 *
 * The `Bus` class simulates a bus's behavior, including its movement along a route with predefined stops.
 * It extends the `Car` class and supports the functionality to visit the next stop in its route. The bus
 * moves at a defined speed and waits at each stop before moving to the next. The stops are cycled through
 * in a loop, ensuring the bus continuously follows its route. The bus's behavior also includes a waiting 
 * period at each stop before continuing.
 */

/**
 * @brief Constructs a Bus object with specified id, spawn building, stops, and speed.
 * 
 * @param id The unique id of the bus.
 * @param spawnBuilding A shared pointer to the building where the bus spawns.
 * @param stops A vector of shared pointers to the buildings that the bus will stop at.
 * @param speed The speed at which the bus moves.
 */
Bus::Bus(int id, std::shared_ptr<Building> spawnBuilding,
         std::vector<std::shared_ptr<Building>> stops, float speed)
    : Car(id, spawnBuilding, speed), stops_(std::move(stops)) {}

/**
 * @brief Gets the stops for the bus.
 * 
 * @return A constant reference to a vector of shared pointers to Building objects representing the bus stops.
 */
const std::vector<std::shared_ptr<Building>>& Bus::getStops() const {
  return stops_;
}

/**
 * @brief Visits the next stop in the bus's route.
 * 
 * The bus drives to the next stop, waits for a period (controlled by waitTime_), 
 * and then updates the current stop index. The bus loops through the stops cyclically.
 */
void Bus::visitNextStop() {
    if (waitTime_ == 0) {
        bool arrived = drive(stops_[currentStopIndex_]->getAdjacentCell());

        if (arrived) {
            waitTime_ = 80;  ///< The bus waits for 80 units of time after reaching a stop.
            currentStopIndex_ = (currentStopIndex_ + 1) % nofStops_;  ///< Move to the next stop, looping if necessary.
        }
    } else {
        waitTime_--;  ///< Decrement the wait time while the bus is waiting at the stop.
    }
}
