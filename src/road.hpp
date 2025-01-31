#ifndef ROAD_HPP
#define ROAD_HPP

#include "intersection.hpp"
#include "car.hpp"
#include "direction_enum.h"
#include "../libs/nlohmann/json.hpp"
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <utility>

class Car;

class Road {
public:
    Road(int id, std::shared_ptr<Intersection> from, std::shared_ptr<Intersection> end, int capacity, Direction direction1, Direction direction2);
    Road();
    ~Road() = default; 
    std::shared_ptr<Car> addCar(std::shared_ptr<Car> car, Direction direction);

    int getId() const;

    void removeCar(std::shared_ptr<Car> car);

    int getCurrentVehicles() const;

    int getCapacity() const;

    float getCurrentDensity() const;

    std::shared_ptr<Intersection> getFrom() const;

    std::shared_ptr<Intersection> getEnd() const;

    std::vector<int> getLogs();
    
    const int getLength();

    const std::vector<std::shared_ptr<Car>>& getLane1() const;

    const std::vector<std::shared_ptr<Car>>& getLane2() const;

    Direction getDirection1() const;

    Direction getDirection2() const;

    void appendLogToCSV(const std::string &filename);
    
    friend void to_json(nlohmann::json &j, const Road &road);
    friend std::shared_ptr<Road> from_json(const nlohmann::json &j, std::vector<std::shared_ptr<Intersection>> intersections);

private:
    int id_;
    int capacity_;                               
    int length_ = 0;                             
    std::vector<int> logs_ = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  
    int currentVehicles_ = 0;                      
    std::shared_ptr<Intersection> from_;         
    std::shared_ptr<Intersection> end_;          
    std::vector<std::shared_ptr<Car>> lane1_ = {};
    std::vector<std::shared_ptr<Car>> lane2_ = {};
    Direction direction1_;                       
    Direction direction2_;                    
};
void writeRoad(const std::string &filename, std::vector<std::shared_ptr<Road>> roads);
std::vector<std::shared_ptr<Road>> readRoad(const std::string &filename, std::vector<std::shared_ptr<Intersection>> intersections);

#endif
