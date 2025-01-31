#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <utility>
#include <list>
#include <vector>  
#include "direction_enum.h"
#include "road.hpp"
#include "coordinate.h"
#include "entity.hpp"
#include "../libs/nlohmann/json.hpp"
#include <memory>

class Road;
class Sign;

class Intersection:public Entity {
public:
    Intersection(int id, Coordinate coordinate);
    std::shared_ptr<Road> getRoad(Direction direction) const;
    void setRoad(const std::shared_ptr<Road>& road, Direction direction);

    friend void to_json(nlohmann::json &j, const Intersection &i);
    friend std::shared_ptr<Intersection> from_json(const nlohmann::json &j);

private:
    std::list<std::pair<Direction, std::shared_ptr<Road>>> connectedRoads_ = {};
};
void writeIntersection(const std::string &filename, std::vector<std::shared_ptr<Intersection>> intersections);
std::vector<std::shared_ptr<Intersection>> readIntersection(const std::string &filename);
#endif

