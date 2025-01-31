#ifndef CITY_HPP
#define CITY_HPP

#include <string>
#include <vector>

#include "building.hpp"
#include "car.hpp"
#include "person.hpp"
#include "road.hpp"
#include "bus.hpp"
#include <memory>

class City {
public:
    City(int width, int length, long population, 
     const std::vector<std::shared_ptr<Building>>& buildings, 
     const std::vector<std::shared_ptr<Car>>& cars, 
     const std::vector<std::shared_ptr<Person>>& residents, 
     const std::vector<std::shared_ptr<Road>>& roads,
     const std::vector<std::shared_ptr<Intersection>>& intersections,
     const std::vector<std::shared_ptr<Building>>& busStops);
    void advance();
    std::string getState(); 
    int getWidth() const;
    int getLength() const;
    long getPopulation() const;
    const std::vector<std::shared_ptr<Building>>& getBuildings() const;
    const std::vector<std::shared_ptr<Car>>& getCars() const;
    const std::vector<std::shared_ptr<Person>>& getResidents() const;
    const std::vector<std::shared_ptr<Road>>& getRoads() const;
    const std::vector<std::shared_ptr<Intersection>>& getIntersections() const;

    std::map<int, int>& getLog(Coordinate coordinate);

    void drawRoads(sf::RenderWindow& window, sf::Texture& roadTexture, std::vector<sf::Texture>& roadHighlightTextures, float scale) const;
    void drawIntersections(sf::RenderWindow& window, sf::Texture& intersectionTexture, float scale) const;
    void drawBuildings(sf::RenderWindow& window, const std::map<char, sf::Texture>& buildingTextures, float scale) const;
    void drawCars(sf::RenderWindow& window, const std::vector<sf::Texture>& carTextures, float scale, long timeInHour, long timeInMinutes) const;
    void drawBus(sf::RenderWindow& window, sf::Texture& busTexture, float scale) const;

    const std::vector<std::pair<sf::FloatRect, std::shared_ptr<Road>>>& getRoadBounds() const;



private:
    int width_;
    int length_;
    long population_;
    std::vector<std::shared_ptr<Building>> buildings_;
    std::vector<std::shared_ptr<Car>> cars_;
    std::vector<std::shared_ptr<Person>> residents_;
    std::vector<std::shared_ptr<Road>> roads_;
    std::vector<std::shared_ptr<Intersection>> intersections_;
    std::shared_ptr<Bus> bus_;
    

    mutable std::vector<std::pair<sf::FloatRect, std::shared_ptr<Road>>> roadBounds_;
    

};

#endif
