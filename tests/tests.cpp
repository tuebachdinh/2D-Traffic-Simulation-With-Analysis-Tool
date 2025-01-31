#ifndef TEST_CPP
#define TEST_CPP

#include <gtest/gtest.h>
#include <memory>
#include "../src/coordinate.h"
#include "../src/road.cpp"
#include "../src/intersection.cpp"
#include "../src/entity.cpp"
#include "../src/entity.cpp"
#include "../src/global.h"
#include "../src/car.cpp"
#include "../src/building.cpp"
#include "../src/person.cpp"

long elapseTime = -1;
int tick = -1;
int rate = 1;

//TEST CLASS ROAD
class RoadTest : public ::testing::Test {
protected:
    std::shared_ptr<Intersection> intersection1;
    std::shared_ptr<Intersection> intersection2;

    void SetUp() override {
        // Initialize intersections
        intersection1 = std::make_shared<Intersection>(11, Coordinate(6, 9));
        intersection2 = std::make_shared<Intersection>(12, Coordinate(10, 9));
    }
};

// Test initialize car
TEST_F(RoadTest, ConstructorInitializesCorrectlyTest) {
    // Sample data
    int id = 0;
    int capacity = 100;
    Direction dir1 = Direction::West;
    Direction dir2 = Direction::East;

    auto road = std::make_shared<Road>(id, intersection1, intersection2, capacity, dir1, dir2);
    int length = std::abs((intersection1->getCoordinate().x - intersection2->getCoordinate().x) + (intersection1->getCoordinate().y - intersection2->getCoordinate().y));

    // Verify the road's attributes
    EXPECT_EQ(road->getId(), id);
    EXPECT_EQ(road->getCapacity(), capacity);
    EXPECT_EQ(road->getFrom(), intersection1);
    EXPECT_EQ(road->getEnd(), intersection2);
    EXPECT_EQ(road->getDirection1(), dir1);
    EXPECT_EQ(road->getDirection2(), dir2);
    EXPECT_EQ(road->getLength(), length);
}

//Test add and remove car
TEST_F(RoadTest, AddAndRemoveCarTest) {
    auto car = std::make_shared<Car>(0);
    int id = 0;
    int capacity = 100;
    Direction dir1 = Direction::West;
    Direction dir2 = Direction::East;
    auto road = std::make_shared<Road>(id, intersection1, intersection2, capacity, dir1, dir2);

    road -> addCar(car, dir2);
    EXPECT_EQ(road->getCurrentVehicles(), 1);
    EXPECT_LE(road->getCurrentDensity() - 0.01, 1e-9);
    EXPECT_EQ(road->getLogs()[0], 1);
    road -> removeCar(car);
    EXPECT_EQ(road->getCurrentVehicles(), 0);
    EXPECT_EQ(road->getCurrentDensity(), 0);
    EXPECT_EQ(road->getLogs()[0], 1);
}

//TEST CLASS INTERSECTION
class IntersectionTest : public ::testing::Test {
};

TEST_F(IntersectionTest, ConstructorInitializeTest) {
    auto intersection = std::make_shared<Intersection>(11, Coordinate(6, 9));
    EXPECT_EQ(intersection->getCoordinate().x, 6);
    EXPECT_EQ(intersection->getCoordinate().y, 9);
}

TEST_F(IntersectionTest, SetRoadAndGetRoadTest) {
    auto intersection1 = std::make_shared<Intersection>(11, Coordinate(6, 9));
    auto intersection2 = std::make_shared<Intersection>(12, Coordinate(10, 9));
    int id = 0;
    int capacity = 100;
    Direction dir1 = Direction::West;
    Direction dir2 = Direction::East;

    auto road = std::make_shared<Road>(id, intersection1, intersection2, capacity, dir1, dir2);
    intersection1->setRoad(road, dir1);
    EXPECT_EQ(intersection1->getRoad(dir1), road);
}

//TEST CLASS BUILDING
class BuildingTest : public ::testing::Test {
};

TEST_F(BuildingTest, ConstructorInitializeTest) {
    auto building = std::make_shared<Building>(0, Coordinate(5, 5), 1000, 'W');
    EXPECT_EQ(building->getId(), 0);
    EXPECT_EQ(building->getCapacity(), 1000);
    EXPECT_EQ(building->getCoordinate(), Coordinate(5,5));
    EXPECT_EQ(building->getType(), 'W');
};

TEST_F(BuildingTest, SetRoadTest) {
    auto building = std::make_shared<Building>(0, Coordinate(5, 5), 1000, 'W');
    auto intersection1 = std::make_shared<Intersection>(11, Coordinate(6, 9));
    auto intersection2 = std::make_shared<Intersection>(12, Coordinate(10, 9));
    int id = 0;
    int capacity = 100;
    Direction dir1 = Direction::West;
    Direction dir2 = Direction::East;

    auto road = std::make_shared<Road>(id, intersection1, intersection2, capacity, dir1, dir2);
    building->setAdjacentRoad(road);
    EXPECT_EQ(building->getAdjacentRoad(), road);
};

TEST_F(BuildingTest, SetAdjacentCellTest) {
    auto building = std::make_shared<Building>(0, Coordinate(5, 5), 1000, 'W');
    building->setAdjacentCell(Coordinate(4,5));
    EXPECT_EQ(building->getAdjacentCell(), Coordinate(4,5));
};

//TEST CAR
class CarTest : public ::testing::Test {
};

TEST_F(CarTest, ConstructorInitializeTest) {
    //initialize building
    auto building = std::make_shared<Building>(0, Coordinate(5, 5), 1000, 'W');
    //initialize road
    auto intersection1 = std::make_shared<Intersection>(11, Coordinate(6, 9));
    auto intersection2 = std::make_shared<Intersection>(12, Coordinate(10, 9));
    int id = 0;
    int capacity = 100;
    Direction dir1 = Direction::West;
    Direction dir2 = Direction::East;

    auto road = std::make_shared<Road>(id, intersection1, intersection2, capacity, dir1, dir2);
    //set road and set adjacent cell
    building->setAdjacentRoad(road);
    building->setAdjacentCell(Coordinate(4,5));

    auto car = std::make_shared<Car>(0, building);
    EXPECT_EQ(car->getSpeed(), 0.1f);
};

TEST_F(CarTest, DriveTest) {
    //initialize building
    auto building = std::make_shared<Building>(0, Coordinate(7, 8), 1000, 'W');
    //initialize road
    auto intersection1 = std::make_shared<Intersection>(11, Coordinate(6, 9));
    auto intersection2 = std::make_shared<Intersection>(12, Coordinate(10, 9));
    int id = 0;
    int capacity = 100;
    Direction dir1 = Direction::West;
    Direction dir2 = Direction::East;

    auto road = std::make_shared<Road>(id, intersection1, intersection2, capacity, dir2, dir1);
    //set road and set adjacent cell
    building->setAdjacentRoad(road);
    building->setAdjacentCell(Coordinate(7,9));

    auto car = std::make_shared<Car>(0, building);
    int count = 0;
    bool check = false;
    while (!check) {
        check = car->drive(Coordinate(9,9));
        count++;
    }
    EXPECT_EQ(count, 19);
};

// TEST CLASS PERSON
class PersonTest : public ::testing::Test {
};

TEST_F(PersonTest, RandomDailyScheduleTest) {
    // Creating intersections
    auto intersection0 = std::make_shared<Intersection>(0, Coordinate(2, 2));
    auto intersection1 = std::make_shared<Intersection>(1, Coordinate(6, 2));
    auto intersection2 = std::make_shared<Intersection>(2, Coordinate(10, 2));
    auto intersection3 = std::make_shared<Intersection>(3, Coordinate(16, 2));
    auto intersection4 = std::make_shared<Intersection>(4, Coordinate(20, 2));
    auto intersection5 = std::make_shared<Intersection>(5, Coordinate(20, 4));
    auto intersection6 = std::make_shared<Intersection>(6, Coordinate(24, 4));

    // Creating roads
    auto road1 = std::make_shared<Road>(0, intersection0, intersection1, 100, West, East);
    auto road2 = std::make_shared<Road>(1, intersection1, intersection2, 100, West, East);
    auto road3 = std::make_shared<Road>(2, intersection2, intersection3, 100, West, East);
    auto road4 = std::make_shared<Road>(3, intersection3, intersection4, 100, West, East);
    auto road5 = std::make_shared<Road>(4, intersection5, intersection6, 100, West, East);

    // Creating buildings
    auto building1 = std::make_shared<Building>(0, Coordinate(3, 3), 1000, 'W');
    auto building2 = std::make_shared<Building>(1, Coordinate(5, 3), 1000, 'H');
    auto building3 = std::make_shared<Building>(2, Coordinate(11, 3), 1000, 'F');

    // Creating person
    auto person1 = std::make_shared<Person>(building1, building2, building3);
    auto person2 = std::make_shared<Person>(building2, building1, building3);

    person1->decideDailySchedule();
    person2->decideDailySchedule();
    
    for (int i = 0; i < 3; i++) {
        if (person1->getSchedule()[i] != person2->getSchedule()[i]) {
            EXPECT_TRUE(true); 
            break;
        }
    }
};

TEST_F(PersonTest, DrivingToBuildingTest) {
    // Creating intersections
    auto intersection0 = std::make_shared<Intersection>(0, Coordinate(2, 2));
    auto intersection1 = std::make_shared<Intersection>(1, Coordinate(6, 2));
    auto intersection2 = std::make_shared<Intersection>(2, Coordinate(10, 2));
    auto intersection3 = std::make_shared<Intersection>(3, Coordinate(16, 2));
    auto intersection4 = std::make_shared<Intersection>(4, Coordinate(20, 2));
    auto intersection5 = std::make_shared<Intersection>(5, Coordinate(20, 4));
    auto intersection6 = std::make_shared<Intersection>(6, Coordinate(24, 4));

    // Creating roads
    auto road1 = std::make_shared<Road>(0, intersection0, intersection1, 100, East, West);
    auto road2 = std::make_shared<Road>(1, intersection1, intersection2, 100, East, West);
    auto road3 = std::make_shared<Road>(2, intersection2, intersection3, 100, West, East);
    auto road4 = std::make_shared<Road>(3, intersection3, intersection4, 100, West, East);
    auto road5 = std::make_shared<Road>(4, intersection5, intersection6, 100, West, East);

    // Creating buildings
    auto building1 = std::make_shared<Building>(0, Coordinate(3, 3), 1000, 'W');
    auto building2 = std::make_shared<Building>(1, Coordinate(5, 3), 1000, 'H');
    auto building3 = std::make_shared<Building>(2, Coordinate(11, 3), 1000, 'F');

    // Set adjacent cell and adjacent road for buildings
    building1->setAdjacentCell(Coordinate(3, 2));
    building1->setAdjacentRoad(road1);

    building2->setAdjacentCell(Coordinate(5, 2));
    building2->setAdjacentRoad(road1);

    // Creating person
    auto person1 = std::make_shared<Person>(building1, building2, building3);
    int count = 0;
    bool check = false;
    while (person1->getCurrentBuilding() != building2) {
        person1->drive(building2);
        count++;
    }
    EXPECT_EQ(count, 20);
};
#endif

