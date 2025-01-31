#ifndef CITY_CPP
#define CITY_CPP

#include "city.hpp"
#include "global.h"

/**
 * @class City
 * @brief Represents a city with buildings, cars, residents, roads, intersections, and a bus.
 */
City::City(int width, int length, long population, 
           const std::vector<std::shared_ptr<Building>>& buildings, 
           const std::vector<std::shared_ptr<Car>>& cars, 
           const std::vector<std::shared_ptr<Person>>& residents, 
           const std::vector<std::shared_ptr<Road>>& roads,
           const std::vector<std::shared_ptr<Intersection>>& intersections,
           const std::vector<std::shared_ptr<Building>>& busStops): 
    width_(width),             
    length_(length),           
    population_(population),            
    buildings_(buildings),
    cars_(cars),
    residents_(residents),
    roads_(roads),
    intersections_(intersections) {
    
    for (auto& building : buildings_) {
        int x = building->getCoordinate().x;
        int y = building->getCoordinate().y;

        for (auto& road : roads_) {
            int fromX = road->getFrom()->getCoordinate().x;
            int fromY = road->getFrom()->getCoordinate().y;
            int toX = road->getEnd()->getCoordinate().x;
            int toY = road->getEnd()->getCoordinate().y;

            std::vector<std::pair<int, int>> adjacentCells = {
                {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}
            };

            for (auto& cell : adjacentCells) {
                int cellX = cell.first;
                int cellY = cell.second;

                if (fromX == toX && cellX == fromX && 
                    cellY >= std::min(fromY, toY) && cellY <= std::max(fromY, toY)) {
                    building->setAdjacentRoad(road);
                    building->setAdjacentCell(Coordinate(cellX, cellY));

                } else if (fromY == toY && cellY == fromY && 
                    cellX >= std::min(fromX, toX) && cellX <= std::max(fromX, toX)) {
                    building->setAdjacentRoad(road);
                    building->setAdjacentCell(Coordinate(cellX, cellY));
                }
            }
            
        }
    }

    bus_ = std::make_shared<Bus>(-9, buildings[21], busStops);

}

/**
 * @brief Advances the simulation by one time tick.
 *        Updates the time and calls actions for each resident and the bus.
 */
void City::advance() {
    tick = (tick + 1) % 5;
    if (tick == 0) {
        elapseTime ++;
    }
    for (const auto& person:residents_) {
        person->action();
    }
    bus_->visitNextStop();
}

/**
 * @brief Gets the width of the city.
 * @return The width of the city.
 */
int City::getWidth() const {
    return width_;
}


/**
 * @brief Gets the length of the city.
 * @return The length of the city.
 */
int City::getLength() const {
    return length_;
}

/**
 * @brief Gets the population of the city.
 * @return The population of the city.
 */
long City::getPopulation() const {
    return population_;
}

/**
 * @brief Gets the list of buildings in the city.
 * @return A reference to the vector of building shared pointers.
 */
const std::vector<std::shared_ptr<Building>>& City::getBuildings() const {
    return buildings_;
}

/**
 * @brief Gets the list of cars in the city.
 * @return A reference to the vector of car shared pointers.
 */
const std::vector<std::shared_ptr<Car>>& City::getCars() const {
    return cars_;
}

/**
 * @brief Gets the list of residents in the city.
 * @return A reference to the vector of resident shared pointers.
 */
const std::vector<std::shared_ptr<Person>>& City::getResidents() const {
    return residents_;
}

/**
 * @brief Gets the list of roads in the city.
 * @return A reference to the vector of road shared pointers.
 */
const std::vector<std::shared_ptr<Road>>& City::getRoads() const {
    return roads_;
}

/**
 * @brief Gets the list of intersections in the city.
 * @return A reference to the vector of intersection shared pointers.
 */
const std::vector<std::shared_ptr<Intersection>>& City::getIntersections() const {
    return intersections_;
}

/**
 * @brief Gets the road bounds for rendering.
 * @return A reference to the vector of road bounds and associated roads.
 */
const std::vector<std::pair<sf::FloatRect, std::shared_ptr<Road>>>& City::getRoadBounds() const {
    return roadBounds_;
}

/**
 * @brief Draws all the roads in the city.
 * @param window The SFML window to render to.
 * @param roadTexture The texture for the road.
 * @param roadHighlightTextures Textures for highlighted roads.
 * @param scale The scale factor for rendering.
 */
void City::drawRoads(sf::RenderWindow& window, sf::Texture& roadTexture, std::vector<sf::Texture>& roadHighlightTextures, float scale) const {
    roadBounds_.clear();
    for (const auto& road : roads_) {
        sf::Texture mainRoadTexture;
        if (HIGHLIGHT_MODE) {
            auto currentVehicles = road->getCurrentVehicles();
            mainRoadTexture = currentVehicles < 4 ? roadHighlightTextures[currentVehicles] : roadHighlightTextures[3]; 
        } else {
            mainRoadTexture = roadTexture;
        }
        auto from = road->getFrom()->getCoordinate();
        auto to = road->getEnd()->getCoordinate();
        float dx = (to.x - from.x) * scale;
        float dy = (to.y - from.y) * scale; 

        float roadLength = std::sqrt(dx * dx + dy * dy);

        float scaledTileWidth = mainRoadTexture.getSize().x * 2.0f; 
        int numTiles = static_cast<int>(std::ceil(roadLength / scaledTileWidth));

        if (std::abs(dx) > std::abs(dy)) { 
            numTiles = std::max(1, numTiles - 1); 
        }

        sf::Vector2f direction(dx / roadLength, dy / roadLength);

        for (int i = 0; i < numTiles; ++i) {
            sf::Sprite roadSprite;
            roadSprite.setTexture(mainRoadTexture);

            sf::Vector2f tilePosition(
                from.x * scale + direction.x * i * scaledTileWidth,
                from.y * scale + direction.y * i * scaledTileWidth
            );
            roadSprite.setPosition(tilePosition);

            float angle = atan2(dy, dx) * 180 / 3.14159f;
            roadSprite.setRotation(angle);

            roadSprite.setScale(2.0f, 2.0f);

            // Calculate and store bounding box
            sf::FloatRect roadBoundsBox(
                tilePosition.x -32, tilePosition.y,
                scaledTileWidth * 2.0f, scaledTileWidth * 2.0f
            );
            roadBounds_.emplace_back(roadBoundsBox, road);

            window.draw(roadSprite);
        }
    }
}


/**
 * @brief Draws all the intersections in the city.
 * @param window The SFML window to render to.
 * @param intersectionTexture The texture for the intersection.
 * @param scale The scale factor for rendering.
 */
void City::drawIntersections(sf::RenderWindow& window, sf::Texture& intersectionTexture, float scale) const {
    for (const auto& intersection : intersections_) {
        sf::Sprite intersectionSprite;
        intersectionSprite.setTexture(intersectionTexture);

        auto coord = intersection->getCoordinate();
        intersectionSprite.setPosition(coord.x * scale - 32, coord.y * scale);
        intersectionSprite.setScale(2.0f, 2.0f);

        window.draw(intersectionSprite);
    }
}

/**
 * @brief Draws all the buildings in the city.
 * @param window The SFML window to render to.
 * @param buildingTextures A map of building textures by type.
 * @param scale The scale factor for rendering.
 */
void City::drawBuildings(sf::RenderWindow& window, const std::map<char, sf::Texture>& buildingTextures, float scale) const {
    for (const auto& building : buildings_) {
        sf::Sprite buildingSprite;
        char buildingType = building->getType();

        if (buildingTextures.find(buildingType) != buildingTextures.end()) {
            buildingSprite.setTexture(buildingTextures.at(buildingType));
        } else {
            std::cerr << "Texture not found for building type: " << buildingType << std::endl;
            continue;
        }

        auto coord = building->getCoordinate();
        buildingSprite.setPosition(coord.x * scale - 30, coord.y * scale);
        buildingSprite.setScale(2.0f, 2.0f);

        window.draw(buildingSprite);
        
    }
}

/**
 * @brief Draws all the cars in the city.
 * @param window The SFML window to render to.
 * @param carTextures The textures for the car.
 * @param scale The scale factor for rendering.
 * @param timeInHour The current time in hours.
 * @param timeInMinutes The current time in minutes.
 */
void City::drawCars(sf::RenderWindow& window, const std::vector<sf::Texture>& carTextures, float scale, long timeInHour, long timeInMinutes) const {
    for (const auto& resident : residents_) {
        auto car = resident->getCar(); 
        if (car) {
            sf::Sprite carSprite;

            std::uintptr_t index = reinterpret_cast<std::uintptr_t>(car.get()) % carTextures.size();

            const sf::Texture& carTexture = carTextures[index];
            carSprite.setTexture(carTexture);
            auto carCoord = car->getCoordinate();
            auto direction = car->getDirection();

            if (direction == West) {
                carSprite.setScale(-1.0f, 1.0f);
                carSprite.setOrigin(carTexture.getSize().x, 0);
                carSprite.setPosition(carCoord.x * scale - 8, carCoord.y * scale + 4);
            } else if (direction == East) {
                carSprite.setScale(1.0f, 1.0f);
                carSprite.setOrigin(0, 0);
                carSprite.setPosition(carCoord.x * scale - 8, carCoord.y * scale + 16);
            } else if (direction == North) {
                carSprite.setRotation(-90);
                carSprite.setPosition(carCoord.x * scale - 8, carCoord.y * scale + 8);
            } else if (direction == South) {
                carSprite.setRotation(90);
                carSprite.setPosition(carCoord.x * scale - 20, carCoord.y * scale + 8);
            }

            carSprite.setOrigin(carTexture.getSize().x / 2, carTexture.getSize().y / 2);
            window.draw(carSprite);

        }
    }
}

/**
 * @brief Draws the bus in the city.
 * @param window The SFML window to render to.
 * @param busTexture The texture for the bus.
 * @param scale The scale factor for rendering.
 */
void City::drawBus(sf::RenderWindow& window, sf::Texture& busTexture, float scale) const {
    sf::Sprite busSprite;
    busSprite.setTexture(busTexture);

    auto busCoord = bus_->getCoordinate();
    auto direction = bus_->getDirection();
    
    if (direction == West) {
        busSprite.setScale(-0.15f, 0.15f);
        busSprite.setOrigin(busTexture.getSize().x, 0);
        busSprite.setPosition(busCoord.x * scale - 8, busCoord.y * scale + 8);
    } else if (direction == East) {
        busSprite.setScale(0.15f, 0.15f);
        busSprite.setOrigin(0, 0);
        busSprite.setPosition(busCoord.x * scale - 8, busCoord.y * scale + 20);
    } else if (direction == North) {
        busSprite.setScale(0.15f, 0.15f);
        busSprite.setRotation(-90);
        busSprite.setPosition(busCoord.x * scale - 8, busCoord.y * scale + 8);
    } else if (direction == South) {
        busSprite.setScale(0.15f, 0.15f);
        busSprite.setRotation(90);
        busSprite.setPosition(busCoord.x * scale - 20, busCoord.y * scale + 8);
    }

    busSprite.setOrigin(busTexture.getSize().x / 2, busTexture.getSize().y / 2);
    window.draw(busSprite);
}


#endif