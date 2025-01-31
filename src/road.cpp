#ifndef ROAD_CPP
#define ROAD_CPP

#include "road.hpp"
#include "car.hpp"
#include "coordinate.h"
#include "direction_enum.h"
#include "../libs/nlohmann/json.hpp"
#include <fstream>
#include "intersection.hpp"
#include "global.h"
#include <iostream>

/**
 * @class Road
 * @brief Represents a road between two intersections with capacity, length, and direction.
 *
 * This class models a road between two intersections. It contains information about the road's
 * capacity, current number of vehicles, length, and direction. It also allows cars to be added or
 * removed from the road, and stores logs of traffic data.
 */
Road::Road(int id, std::shared_ptr<Intersection> from, std::shared_ptr<Intersection> end, int capacity, Direction direction1, Direction direction2)
    : id_(id), from_(from), end_(end), capacity_(capacity), direction1_(direction1), direction2_(direction2)
{

    if (!from || !end)
    {
        throw std::runtime_error("Invalid Intersection pointers passed to Road constructor");
    }
    length_ = std::abs((from_->getCoordinate().x - end_->getCoordinate().x) +
                       (from_->getCoordinate().y - end_->getCoordinate().y));
    currentVehicles_ = 0;
}

/**
 * @brief Default constructor for a Road.
 *
 * Creates an empty road object, used for initialize with JSON.
 */
Road::Road() {};

/**
 * @brief Gets the ID of the road.
 * @return The ID of the road as an integer.
 */
int Road::getId() const
{
    return id_;
}

// bool Road::loadTexture(const std::string& texturePath) {
//     if (!roadTexture_.loadFromFile(texturePath)) {
//         std::cerr << "Failed to load texture: " << texturePath << std::endl;
//         return false;
//     }
//     roadSprite_.setTexture(roadTexture_);
//     return true;
// }

// sf::Sprite& Road::getSprite() {
//     return roadSprite_;
// }

/**
 * @brief Gets the current number of vehicles on the road.
 * @return The number of vehicles on the road.
 */
int Road::getCurrentVehicles() const
{
    return currentVehicles_;
}

/**
 * @brief Gets the capacity of the road.
 * @return The capacity of the road.
 */
int Road::getCapacity() const
{
    return capacity_;
}

/**
 * @brief Gets the starting intersection of the road.
 * @return A shared pointer to the starting intersection.
 */
std::shared_ptr<Intersection> Road::getFrom() const
{
    return from_;
}

/**
 * @brief Gets the current vehicle density on the road.
 * @return A float representing the vehicle density (currentVehicles / capacity).
 */
float Road::getCurrentDensity() const { return 1.0f * currentVehicles_ / capacity_; }

/**
 * @brief Gets the ending intersection of the road.
 * @return A shared pointer to the ending intersection.
 */
std::shared_ptr<Intersection> Road::getEnd() const
{
    return end_;
}

/**
 * @brief Gets the traffic logs for the road.
 * @return A vector containing the traffic logs for the road.
 */
std::vector<int> Road::getLogs() { return logs_; }

// TODO: dequeue
/**
 * @brief Adds a car to the road in the specified direction.
 * @param car A shared pointer to the car to be added.
 * @param direction The direction in which the car is traveling.
 * @return A shared pointer to the car in front of the added car, or nullptr if the car is the first in line.
 */
std::shared_ptr<Car> Road::addCar(std::shared_ptr<Car> car, Direction direction)
{
    std::shared_ptr<Car> carInfront = nullptr;
    int timeInHour = (elapseTime * rate / 60) % 24;
    if (currentVehicles_ < capacity_)
    {
        if (direction == direction1_)
        {
            carInfront = lane1_.empty() ? nullptr : lane1_.back();
            lane1_.push_back(car);
        }
        else if (direction == direction2_)
        {
            carInfront = lane2_.empty() ? nullptr : lane2_.back();
            lane2_.push_back(car);
        }
        ++currentVehicles_;
        logs_[timeInHour] = logs_[timeInHour] + 1;
        return carInfront;
    }
    return nullptr;
}

/**
 * @brief Removes a car from the road.
 * @param car A shared pointer to the car to be removed.
 *
 * This function removes the specified car from either lane 1 or lane 2.
 */
void Road::removeCar(std::shared_ptr<Car> car)
{ // UNCALLED
    int i = 0;
    currentVehicles_ = currentVehicles_ > 0 ? currentVehicles_ - 1 : 0;
    for (auto carOnRoad : lane1_)
    {
        if (carOnRoad == car)
        {
            lane1_.erase(lane1_.begin() + i);
            return;
        }
        i++;
    }
    i = 0;
    for (auto carOnRoad : lane2_)
    {
        if (carOnRoad == car)
        {
            lane2_.erase(lane2_.begin() + i);
            return;
        }
        i++;
    }
}

/**
 * @brief Gets the cars on lane 1 of the road.
 * @return A constant reference to the vector of cars on lane 1.
 */
const std::vector<std::shared_ptr<Car>> &Road::getLane1() const
{
    return lane1_;
}

/**
 * @brief Gets the length of the road.
 * @return The length of the road.
 */
const int Road::getLength() { return length_; }

/**
 * @brief Gets the cars on lane 2 of the road.
 * @return A constant reference to the vector of cars on lane 2.
 */
const std::vector<std::shared_ptr<Car>> &Road::getLane2() const
{
    return lane2_;
}

/**
 * @brief Gets the first direction of the road.
 * @return The first direction as a `Direction` value.
 */
Direction Road::getDirection1() const
{
    return direction1_;
}

/**
 * @brief Gets the second direction of the road.
 * @return The second direction as a `Direction` value.
 */
Direction Road::getDirection2() const
{
    return direction2_;
}

/**
 * @brief Serializes a Road object to JSON.
 * @param j The JSON object to write the serialized data to.
 * @param road The Road object to serialize.
 */
void to_json(nlohmann::json &j, const Road &road)
{
    j = nlohmann::json{
        {"id", road.getId()},
        {"capacity", road.capacity_},
        {"length", road.length_},
        {"from", road.getFrom()->getId()},
        {"end", road.getEnd()->getId()},
        {"currentVehicles", road.currentVehicles_},
        {"direction1", road.direction1_},
        {"direction2", road.direction2_},
        {"logs", nlohmann::json::array()}};

    // Serialize logs
    // for (int i = 0; i <24; i++)
    // {
    //     j["logs"].push_back({ {"vehicles", road.getLogs().second}});
    // }
}

/**
 * @brief Deserializes a Road object from JSON.
 * @param j The JSON object containing the data.
 * @param intersections The list of intersections to associate with the road.
 * @return A shared pointer to the deserialized Road object.
 */
std::shared_ptr<Road> from_json(const nlohmann::json &j, std::vector<std::shared_ptr<Intersection>> intersections)
{
    int id;
    int capacity;
    int length;
    int currentVehicles;
    Direction direction1;
    Direction direction2;
    int fromId;
    int endId;

    j.at("id").get_to(id);
    j.at("capacity").get_to(capacity);
    j.at("currentVehicles").get_to(currentVehicles);
    j.at("direction1").get_to(direction1);
    j.at("direction2").get_to(direction2);
    j.at("from").get_to(fromId);
    j.at("end").get_to(endId);

    auto road = std::make_shared<Road>(id, intersections[fromId], intersections[endId], capacity, direction1, direction2);
    intersections[fromId]->setRoad(road, direction2);
    intersections[endId]->setRoad(road, direction1);
    return road;
}

/**
 * @brief Writes a list of roads to a JSON file.
 * @param filename The name of the file to write to.
 * @param roads A vector of shared pointers to Road objects to write.
 * @throws std::ios_base::failure If the file cannot be opened for writing.
 * @throws std::invalid_argument If a nullptr is encountered in the roads vector.
 */
void writeRoad(const std::string &filename, std::vector<std::shared_ptr<Road>> roads)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        throw std::ios_base::failure("Failed to open file for writing: " + filename);
    }

    nlohmann::json jsonArray = nlohmann::json::array();

    for (const auto &road : roads)
    {
        if (road != nullptr)
        {
            jsonArray.push_back(*road);
        }
        else
        {
            throw std::invalid_argument("Encountered nullptr in roads vector.");
        }
    }

    outFile << jsonArray.dump(4);
    outFile.close();
}

/**
 * @brief Reads a list of roads from a JSON file.
 * @param filename The name of the file to read from.
 * @param intersections A vector of shared pointers to intersections to associate with the roads.
 * @return A vector of shared pointers to the deserialized Road objects.
 * @throws std::ios_base::failure If the file cannot be opened for reading.
 */
std::vector<std::shared_ptr<Road>> readRoad(const std::string &filename, std::vector<std::shared_ptr<Intersection>> intersections)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        throw std::ios_base::failure("Failed to open file for reading: " + filename);
    }

    nlohmann::json jsonArray;
    inFile >> jsonArray;

    std::vector<std::shared_ptr<Road>> roads;

    for (const auto &j : jsonArray)
    {
        roads.push_back(from_json(j, intersections));
    }

    return roads;
}

/**
 * @brief Appends the road log data to a CSV file.
 * 
 * This function opens the specified CSV file in append mode, writes a header if the file is empty,
 * and appends the road log data for each hour (from 0 to 23). The function first checks if the file
 * is empty, and if so, writes the header with column names. It then appends the log data for the
 * specific road identified by its ID.
 *
 * @param filename The name of the CSV file where the log data will be appended.
 * 
 * @note The function assumes that the `logs_` map contains log data for 24 hours (one for each hour of the day).
 *       It writes the log data for each hour as comma-separated values.
 */

void Road::appendLogToCSV(const std::string &filename)
{
    // Open the file in append mode
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Check if the file is empty to write the header (optional)
    std::ifstream checkFile(filename);
    if (checkFile.peek() == std::ifstream::traits_type::eof())
    {
        file << "ROADS,Hour 0,Hour 1,Hour 2,Hour 3,Hour 4,Hour 5,Hour 6,Hour 7,Hour 8,Hour 9,Hour 10,Hour 11,Hour 12,Hour 13,Hour 14,Hour 15,Hour 16,Hour 17,Hour 18,Hour 19,Hour 20,Hour 21,Hour 22,Hour 23,\n"; // Write header if the file is empty
    }
    checkFile.close();
    file << "Road " << id_ << ",";
    // Iterate over the logs_ map and append each entry to the file
    for (int i = 0; i < 24; i++)
    {
        file << logs_[i] << ",";
    }
    file << '\n'
         << std::endl;

    file.close();
}
#endif
