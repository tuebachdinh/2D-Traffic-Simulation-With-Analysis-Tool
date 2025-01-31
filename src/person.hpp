#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include "../libs/nlohmann/json.hpp"
#include "building.hpp"

enum Action {
    Work,
    Play,
    Home
};

class Person {
public:
    Person(std::shared_ptr<Building> home, std::shared_ptr<Building> work, std::shared_ptr<Building> favBuilding);

    bool isDriving() const;

    void setDriving(bool driving);

    Action getCurrentAction() const;

    void action(); 

    void decideDailySchedule();

    void drive(std::shared_ptr<Building> dest);

    void performAction(); 

    std::shared_ptr<Car> getCar();

    std::vector<int> getSchedule();

    std::shared_ptr<Building> getCurrentBuilding();

    friend void to_json(nlohmann::json &j, const Person &person);
    friend std::shared_ptr<Person> from_json(const nlohmann::json &j, Person &person, std::vector<std::shared_ptr<Building>> buildings);

private:
    std::shared_ptr<Building> home_;
    std::shared_ptr<Building> work_;
    std::shared_ptr<Building> favBuilding_;
    std::shared_ptr<Building> currentBuilding_;
    bool arrived_ = false;
    bool driving_;
    Action currentAction_;
    int minuteRemainder_;
    int goToWorkTime_;
    int homeFromWorkTime_;
    int playTime_;
    int homeFromPlayTime_;
    std::shared_ptr<Car> car_ = nullptr;
};
void writePerson(const std::string &filename, const std::vector<std::shared_ptr<Person>> people);
std::vector<std::shared_ptr<Person>> readPerson(const std::string &filename, std::vector<std::shared_ptr<Building>> buildings);

#endif

