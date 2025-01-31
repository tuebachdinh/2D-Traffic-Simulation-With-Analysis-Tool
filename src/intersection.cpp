#ifndef INTERSECTION_CPP
#define INTERSECTION_CPP

#include <utility>
#include <list>
#include <vector>
#include <fstream>
#include "direction_enum.h"
#include "road.hpp"
#include "coordinate.h"
#include "intersection.hpp"

/**
 * @class Intersection
 * @brief Represents an intersection with roads and coordinates.
 *
 * This class provides functionality to manage an intersection, including
 * associating it with roads in different directions and providing methods
 * to create intersections from JSON data.
 */
Intersection::Intersection(int id, Coordinate coordinate)
    : Entity(id,coordinate) {}

/**
 * @brief Retrieves the road associated with the given direction.
 * @param direction The direction of the road.
 * @return A shared pointer to the corresponding road or nullptr if not found.
 */
std::shared_ptr<Road> Intersection::getRoad(Direction direction) const {
    for (const auto& road_pair : connectedRoads_) {
        if (road_pair.first == direction) {
            return road_pair.second;
        }
    }
    return nullptr;  
}

/**
 * @brief Sets a road for the intersection in the given direction.
 * @param road A shared pointer to the road to set.
 * @param direction The direction of the road.
 */
void Intersection::setRoad(const std::shared_ptr<Road>& road, Direction direction) {
    connectedRoads_.push_back(std::pair(direction, road));
}

/**
 * @brief Serializes an Intersection object into a JSON object.
 * @param j The JSON object to populate.
 * @param intersection The Intersection object to serialize.
 */
void to_json(nlohmann::json &j, const Intersection &intersection)
{
    j = nlohmann::json{
        {"id", intersection.getId()},
        {"coordinate", {{"x", intersection.getCoordinate().x}, {"y", intersection.getCoordinate().y}}}
    };

}

/**
 * @brief Deserializes a JSON object into an Intersection object.
 * @param j The JSON object to deserialize.
 * @return A shared pointer to the deserialized Intersection object.
 */
std::shared_ptr<Intersection> from_json(const nlohmann::json &j)
{
    int id;
    Coordinate coord;

    j.at("id").get_to(id);
    j.at("coordinate").at("x").get_to(coord.x);
    j.at("coordinate").at("y").get_to(coord.y);

    return std::make_shared<Intersection>(id, coord);

}

/**
 * @brief Writes a list of intersections to a JSON file.
 * @param filename The name of the file to write to.
 * @param intersections The list of intersections to write.
 * @throws std::ios_base::failure If the file cannot be opened for writing.
 * @throws std::invalid_argument If the intersections vector contains nullptr.
 */
void writeIntersection(const std::string &filename, std::vector<std::shared_ptr<Intersection>> intersections)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        throw std::ios_base::failure("Failed to open file for writing: " + filename);
    }

    nlohmann::json jsonArray = nlohmann::json::array();

    for (const auto &intersection : intersections)
    {
        if (intersection != nullptr)
        {
            jsonArray.push_back(*intersection);
        }
        else
        {
            throw std::invalid_argument("Encountered nullptr in intersections vector.");
        }
    }

    outFile << jsonArray.dump(4);
    outFile.close();
}

/**
 * @brief Reads a list of intersections from a JSON file.
 * @param filename The name of the file to read from.
 * @return A vector of shared pointers to Intersection objects.
 * @throws std::ios_base::failure If the file cannot be opened for reading.
 */
std::vector<std::shared_ptr<Intersection>> readIntersection(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        throw std::ios_base::failure("Failed to open file for reading: " + filename);
    }

    nlohmann::json jsonArray;
    inFile >> jsonArray;

    std::vector<std::shared_ptr<Intersection>> intersections;

    for (const auto &j : jsonArray) {
        intersections.push_back(from_json(j));
    }

    return intersections;
}

#endif
