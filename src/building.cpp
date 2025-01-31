#ifndef BUILDING_CPP
#define BUILDING_CPP

#include <fstream>
#include <utility>
#include <iostream>
#include "building.hpp"

/**
 * @class Building
 * @brief Represents a building in the simulation with its characteristics and functionality.
 *
 * The `Building` class models a building with properties such as an id, coordinates, capacity, and type (e.g., residential, commercial).
 * It also provides methods to retrieve and modify information about the building, such as its capacity, type, residents, and adjacent road or cell. 
 * The building can be created and exported to and from JSON format, allowing easy reading and writing of building data. 
 * Additionally, this class having adjacent roads or cells for handling drive algorithm.
 */

/**
 * @brief Constructs a Building object with specified id, coordinate, capacity, and type.
 * 
 * @param id The unique id of the building.
 * @param coordinate The coordinates of the building.
 * @param capacity The capacity of the building (number of people it can hold).
 * @param type The type of building (e.g., residential, commercial, etc.).
 */
Building::Building(int id, Coordinate coordinate, int capacity, char type): Entity(id,coordinate), capacity_(capacity), type_(type){}

/**
 * @brief Default constructor for a Building object.
 */
Building::Building() {}

/**
 * @brief Gets the capacity of the building.
 * 
 * @return The capacity of the building.
 */
int Building::getCapacity() const { return capacity_; }

/**
 * @brief Gets the type of the building.
 * 
 * @return The type of the building (e.g., residential, commercial, etc.) as char type.
 */
char Building::getType() const { return type_; }

/**
 * @brief Gets the number of residents in the building.
 * 
 * @return The number of residents.
 */
int Building::getNofResidents() const { return nofResidents_; }

/**
 * @brief Gets the adjacent road of the building.
 * 
 * @return A shared pointer to the adjacent Road object.
 */
const std::shared_ptr<Road> Building::getAdjacentRoad() const { return adjacentRoad_; }

/**
 * @brief Sets the adjacent road of the building.
 * 
 * @param road A shared pointer to the Road object.
 */
void Building::setAdjacentRoad(std::shared_ptr<Road> road) {adjacentRoad_ = road;}

/**
 * @brief Gets the adjacent cell coordinates of the building.
 * 
 * @return The adjacent cell's coordinates.
 */
const Coordinate Building::getAdjacentCell() const { return adjacentCell_; }

/**
 * @brief Sets the adjacent cell coordinates of the building.
 * 
 * @param coordinate The coordinates of the adjacent cell.
 */
void Building::setAdjacentCell(Coordinate coordinate) {adjacentCell_ = coordinate;}

/**
 * @brief Sets the number of residents in the building.
 * 
 * @param nofResidents The number of residents.
 */
void Building::setNofResidents(int nofResidents) {nofResidents_ = nofResidents; }

/**
 * @brief Converts a JSON object to a Building object.
 * 
 * @param j The JSON object to convert.
 * @param i An index for the building (not used in this function).
 * 
 * @return A shared pointer to the newly created Building object.
 */
std::shared_ptr<Building> from_json(const nlohmann::json &j, int i) {
    int id;
    int x;
    int y;
    int capacity;
    char type;
    j.at("id").get_to(id);
    j.at("coordinate").at("x").get_to(x);
    j.at("coordinate").at("y").get_to(y);
    j.at("capacity").get_to(capacity);
    j.at("type").get_to(type);
    return std::make_shared<Building>(id, Coordinate(x,y), capacity, type);
}

/**
 * @brief Converts a Building object to a JSON object.
 * 
 * @param j The JSON object to populate.
 * @param b The Building object to convert.
 */
void to_json(nlohmann::json& j, const Building& b) {
    j = nlohmann::json{
        {"id", b.id_},
        {"coordinate", {{"x", b.coordinate_.x}, {"y", b.coordinate_.y}}},
        {"capacity", b.capacity_},
        {"type", b.type_},
    };
}

/**
 * @brief Writes a vector of Building objects to a file in JSON format.
 * 
 * @param filename The name of the file to write to.
 * @param buildings The vector of Building objects to write.
 * 
 * @throws std::ios_base::failure If the file cannot be opened for writing.
 * @throws std::invalid_argument If the buildings vector contains a null pointer.
 */
void writeBuilding(const std::string &filename, const std::vector<std::shared_ptr<Building>> buildings) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::ios_base::failure("Failed to open file for writing: " + filename);
    }
    nlohmann::json jsonArray = nlohmann::json::array();

    for (auto building : buildings) {
        if (building != nullptr) {
            jsonArray.push_back(*building);
        }
        else {
            throw std::invalid_argument("Encountered nullptr in buildings vector.");
        }
    }

    outFile << jsonArray.dump(4);
    outFile.close();
}

/**
 * @brief Reads a vector of Building objects from a file in JSON format.
 * 
 * @param filename The name of the file to read from.
 * 
 * @return A vector of shared pointers to Building objects.
 * 
 * @throws std::ios_base::failure If the file cannot be opened for reading.
 * @throws std::runtime_error If the JSON structure is invalid.
 */
std::vector<std::shared_ptr<Building>> readBuilding(const std::string &filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::ios_base::failure("Failed to open file for reading: " + filename);
    }

    nlohmann::json jsonArray;
    inFile >> jsonArray;

    std::vector<std::shared_ptr<Building>> buildings;

    for (const auto& j : jsonArray) {
        if (!j.contains("id") || !j.contains("coordinate") || !j.contains("capacity") || !j.contains("type")) {
             throw std::runtime_error("Invalid JSON structure in input file.");
        }
        buildings.push_back(from_json(j, 0));
    }
    return buildings;
}

#endif
