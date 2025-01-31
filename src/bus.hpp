#ifndef BUS_HPP
#define BUS_HPP

#include <vector>
#include <memory>
#include "car.hpp"
#include "building.hpp"

class Bus : public Car {
public:
    Bus(int id, std::shared_ptr<Building> spawnBuilding, std::vector<std::shared_ptr<Building>> stops = {}, float speed = 0.1f);

    const std::vector<std::shared_ptr<Building>>& getStops() const;
    void visitNextStop();

private:
    std::vector<std::shared_ptr<Building>> stops_;
    int currentStopIndex_ = 1;
    int nofStops_ = stops_.size();
    int waitTime_ = 0;
};

#endif