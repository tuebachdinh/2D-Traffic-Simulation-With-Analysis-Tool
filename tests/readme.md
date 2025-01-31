# Test files

- tests.cpp

# Unit Tests

- RoadTest
- IntersectionTest
- BuildingTest
- CarTest
- PersonTest

# Test of Classes

## **Test Class: RoadTest**

**Test Description:**  
Tests the behavior of the `Road` class, including initialization and car management (add/remove operations).

1. **ConstructorInitializesCorrectlyTest**
    - **Description:** Validates that the constructor correctly initializes a road with the expected attributes, including intersections, direction, and capacity.
    - **Expected Result:** All attributes match the expected values.

2. **AddAndRemoveCarTest**
    - **Description:** Tests adding and removing a car from a road, verifying the number of vehicles and road density before and after the operations.
    - **Expected Result:** After adding and removing a car, the vehicle count and density should match the expected values.

---

## **Test Class: IntersectionTest**

**Test Description:**  
Tests the behavior of the `Intersection` class, including correct initialization and setting/getting roads.

1. **ConstructorInitializeTest**
    - **Description:** Verifies that the intersection is initialized with the correct coordinates.
    - **Expected Result:** The coordinates should match the expected values.

2. **SetRoadAndGetRoadTest**
    - **Description:** Tests the setting and retrieval of a road associated with an intersection.
    - **Expected Result:** The correct road should be retrieved when using `getRoad()`.

---

## **Test Class: BuildingTest**

**Test Description:**  
Tests the behavior of the `Building` class, including initialization and interaction with roads and adjacent cells.

1. **ConstructorInitializeTest**
    - **Description:** Validates that the building is initialized correctly with the expected ID, capacity, coordinates, and type.
    - **Expected Result:** All attributes should match the expected values.

2. **SetRoadTest**
    - **Description:** Tests setting an adjacent road for a building and retrieving it.
    - **Expected Result:** The building should correctly return the set adjacent road.

3. **SetAdjacentCellTest**
    - **Description:** Verifies that the building's adjacent cell is set correctly.
    - **Expected Result:** The building should return the correct adjacent cell.

---

## **Test Class: CarTest**

**Test Description:**  
Tests the behavior of the `Car` class, including initialization and the driving behavior.

1. **ConstructorInitializeTest**
    - **Description:** Verifies that the car is initialized correctly with the expected speed.
    - **Expected Result:** The car's speed should match the expected value.

2. **DriveTest**
    - **Description:** Tests the driving behavior of a car, simulating the movement from one building to another and counting the number of steps.
    - **Expected Result:** The car should reach its destination after the expected number of steps.

---

## **Test Class: PersonTest**

**Test Description:**  
Tests the behavior of the `Person` class, including daily schedule creation and driving to a building.

1. **RandomDailyScheduleTest**
    - **Description:** Verifies that two persons can generate different daily schedules when calling `decideDailySchedule()`.
    - **Expected Result:** The schedules should differ between two persons.

2. **DrivingToBuildingTest**
    - **Description:** Simulates a person driving from one building to another and counts the number of steps to reach the destination.
    - **Expected Result:** The person should reach their destination after the expected number of steps.
