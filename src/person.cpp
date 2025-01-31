#ifndef PERSON_CPP
#define PERSON_CPP

#include "person.hpp"
#include "global.h"
#include <fstream>
#include <iostream>

/**
 * @class Person
 * @brief Represents a person in the simulation.
 *
 * The `Person` class simulates a person's daily routine, including their activities such as going to work, 
 * going home, and going to their favorite building (e.g., a recreational spot). The class handles scheduling 
 * these activities based on random distributions for timings, and simulates the movement between buildings. 
 * It manages the person's transportation, which involves driving a car to different destinations.
 * 
 * Attributes include the person's home, work, and favorite building, as well as the current action and 
 * state (e.g., driving or not). The class updates the person's current action depending on the time of day 
 * and performs the corresponding action (e.g., going to work, returning home).
 */


/**
 * @brief Constructs a Person object with home, work, and favorite building information.
 * 
 * @param home A shared pointer to the home building.
 * @param work A shared pointer to the work building.
 * @param favBuilding A shared pointer to the favorite building.
 */
Person::Person(std::shared_ptr<Building> home, std::shared_ptr<Building> work, std::shared_ptr<Building> favBuilding)
    : home_(home), work_(work), favBuilding_(favBuilding), currentBuilding_(home), driving_(false), currentAction_(Home) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<double> dist1(22.0, 2.0); 
    std::normal_distribution<double> dist2(8.0, 2.0);   
    std::uniform_int_distribution<int> distMin(0, 59);

    float weight = 0.2;

    minuteRemainder_ = distMin(gen) % 60;
    if (std::uniform_real_distribution<>(0.0, 1.0)(gen) < weight) {
        goToWorkTime_ = static_cast<int>(std::round(dist1(gen))); 
    } else {
        goToWorkTime_ = static_cast<int>(std::round(dist2(gen)));
    }

    goToWorkTime_ %= 24;
    homeFromWorkTime_ = 0;
    playTime_ = 0;
    homeFromPlayTime_ = 0;
}

/**
 * @brief Checks if the person is currently driving.
 * 
 * @return true If the person is driving.
 * @return false If the person is not driving.
 */
bool Person::isDriving() const {
    return driving_;
}

/**
 * @brief Sets whether the person is driving.
 * 
 * @param driving The driving state to set.
 */
void Person::setDriving(bool driving) {
    driving_ = driving;
}

/**
 * @brief Gets the current action of the person.
 * 
 * @return The current action (Work, Home, Play).
 */
Action Person::getCurrentAction() const {
    return currentAction_;
}

/**
 * @brief Decides and performs the person's action based on the current time.
 */
void Person::action() {
    int timeInHour = (elapseTime * rate / 60) % 24;
    int timeInMinute = (elapseTime * rate % 60);
    
    if (elapseTime % (24 * 60) == 1) {
        decideDailySchedule();
        return;
    }
    
    if (timeInHour == goToWorkTime_ && timeInMinute == minuteRemainder_) {
        currentAction_ = Work;
        arrived_ = false;
    } else if (timeInHour == homeFromWorkTime_ && timeInMinute == minuteRemainder_) {
        currentAction_ = Home;
        arrived_ = false;
    } else if (timeInHour == playTime_ && timeInMinute == minuteRemainder_) {
        currentAction_ = Play;
        arrived_ = false;
    } else if (timeInHour == homeFromPlayTime_ && timeInMinute == minuteRemainder_) {
        currentAction_ = Home;
        arrived_ = false;
    }

    performAction();
}

/**
 * @brief Performs the action based on the current action state (Work, Home, Play).
 */
void Person::performAction() {
    switch (currentAction_) {
        case Work:
            if (!arrived_) {
                drive(work_);
            }
            break;
        case Home:
            if (!arrived_) {
                drive(home_);
            }
            break;
        case Play:
            if (!arrived_ && favBuilding_) {
                drive(favBuilding_);
            }
            break;
    }
}

/**
 * @brief Gets the car associated with the person.
 * 
 * @return A shared pointer to the car.
 */
std::shared_ptr<Car> Person::getCar() {
    return car_;
}

/**
 * @brief Gets the daily schedule of the person.
 * 
 * @return A vector containing the times for work, home, and play activities.
 */
std::vector<int> Person::getSchedule() {
    return std::vector<int>{goToWorkTime_, homeFromWorkTime_, playTime_, homeFromPlayTime_};
}

/**
 * @brief Gets the current building the person is located in.
 * 
 * @return A shared pointer to the current building.
 */
std::shared_ptr<Building> Person::getCurrentBuilding() {
    return currentBuilding_;
}

/**
 * @brief Simulates the driving of the person to a specified destination.
 * 
 * @param dest A shared pointer to the destination building.
 */
void Person::drive(std::shared_ptr<Building> dest) {
    if (dest == currentBuilding_) {
        return;
    }

    if (!car_) {
        const std::shared_ptr<Road> initialRoad = currentBuilding_->getAdjacentRoad();
        Coordinate initialCell = currentBuilding_->getAdjacentCell();
        Direction initialDirection = initialRoad->getDirection1(); 
        car_ = std::make_shared<Car>(0, currentBuilding_);
        initialRoad->addCar(car_, initialDirection);
    } else {
        auto result = car_->drive(dest->getAdjacentCell());
        if (result) {
            if (car_->getCurrentRoad()) {
                car_->getCurrentRoad()->removeCar(car_);
            }
            arrived_ = true;
            currentBuilding_ = dest;
            car_.reset();
        }
    }
}

/**
 * @brief Decides the daily schedule for the person based on random distributions.
 */
void Person::decideDailySchedule() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> workTimeLenDist(6, 8);  
    static std::uniform_int_distribution<int> betweenWorkTimeDist(4, 7);
    static std::uniform_int_distribution<int> playTimeLenDist(4, 7);    

    homeFromWorkTime_ = goToWorkTime_ + workTimeLenDist(gen);
    playTime_ = homeFromWorkTime_ + betweenWorkTimeDist(gen);
    homeFromPlayTime_ = playTime_ + playTimeLenDist(gen);
}

/**
 * @brief Creates a Person object from a JSON representation.
 * 
 * @param j The JSON object.
 * @param buildings A vector of shared pointers to buildings.
 * @return A shared pointer to the created Person object.
 */
std::shared_ptr<Person> from_json(const nlohmann::json &j, std::vector<std::shared_ptr<Building>> buildings) {
    int homeId;
    int workId;
    int favBuildingId;

    j.at("home").get_to(homeId);
    j.at("work").get_to(workId);
    j.at("favBuilding").get_to(favBuildingId);

    return std::make_shared<Person>(buildings[homeId], buildings[workId], buildings[favBuildingId]);
}

/**
 * @brief Serializes a Person object to JSON.
 * 
 * @param j The JSON object to write to.
 * @param person The Person object to serialize.
 */
void to_json(nlohmann::json &j, const Person &person) {
    j = nlohmann::json{
        {"home", person.home_->getId()},
        {"work", person.work_->getId()},
        {"favBuilding", person.favBuilding_->getId()}
    };
}

/**
 * @brief Writes a vector of Person objects to a JSON file.
 * 
 * @param filename The filename to write to.
 * @param people A vector of shared pointers to Person objects.
 */
void writePerson(const std::string &filename, const std::vector<std::shared_ptr<Person>> people) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::ios_base::failure("Failed to open file for writing: " + filename);
    }

    nlohmann::json jsonArray = nlohmann::json::array();

    for (auto person : people) {
        if (person != nullptr) {
            jsonArray.push_back(*person);
        } else {
            throw std::invalid_argument("Encountered nullptr in people vector.");
        }
    }

    outFile << jsonArray.dump(4);

    outFile.close();
}

/**
 * @brief Reads a vector of Person objects from a JSON file.
 * 
 * @param filename The filename to read from.
 * @param buildings A vector of shared pointers to buildings.
 * @return A vector of shared pointers to Person objects.
 */
std::vector<std::shared_ptr<Person>> readPerson(const std::string &filename, std::vector<std::shared_ptr<Building>> buildings) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::ios_base::failure("Failed to open file for reading: " + filename);
    }

    nlohmann::json jsonArray;
    inFile >> jsonArray;

    std::vector<std::shared_ptr<Person>> people;

    for (const auto &j : jsonArray) {
        people.push_back(from_json(j, buildings));
    }

    return people;
}

#endif
