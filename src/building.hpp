#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "../libs/nlohmann/json.hpp"
#include "road.hpp"
#include "entity.hpp"

class Building : public Entity {
public:
    Building(int id, Coordinate coordinate , int capacity = -1, char type = 'N');
    Building();

    int getCapacity() const;
    char getType() const;
    int getNofResidents() const;
    const std::shared_ptr<Road> getAdjacentRoad() const;
    void setAdjacentRoad(std::shared_ptr<Road> road);
    const Coordinate getAdjacentCell() const;
    void setAdjacentCell(Coordinate coordinate);
    void setNofResidents(int nofResidents);

    friend void to_json(nlohmann::json &j, const Building &b);
    friend std::shared_ptr<Building> from_json(const nlohmann::json &j, int i);

private :
    std::shared_ptr<Road> adjacentRoad_;
    Coordinate adjacentCell_;
    int capacity_;
    char type_;
    int nofResidents_;

};
void writeBuilding(const std::string &filename, std::vector<std::shared_ptr<Building>> b);
std::vector<std::shared_ptr<Building>> readBuilding(const std::string &filename);
#endif 

