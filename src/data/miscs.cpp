// std::vector<std::shared_ptr<Intersection>> intersections = {
//     std::make_shared<Intersection>(0, Coordinate(2, 2)),
//     std::make_shared<Intersection>(1, Coordinate(6, 2)),
//     std::make_shared<Intersection>(2, Coordinate(10, 2)),
//     std::make_shared<Intersection>(3, Coordinate(16, 2)),
//     std::make_shared<Intersection>(4, Coordinate(20, 2)),
//     std::make_shared<Intersection>(5, Coordinate(20, 4)),
//     std::make_shared<Intersection>(6, Coordinate(24, 4)),
//     std::make_shared<Intersection>(7, Coordinate(28, 4)),
//     std::make_shared<Intersection>(8, Coordinate(14, 5)),
//     std::make_shared<Intersection>(9, Coordinate(16, 5)),
//     std::make_shared<Intersection>(10, Coordinate(2, 9)),
//     std::make_shared<Intersection>(11, Coordinate(6, 9)),
//     std::make_shared<Intersection>(12, Coordinate(10, 9)),
//     std::make_shared<Intersection>(13, Coordinate(14, 9)),
//     std::make_shared<Intersection>(14, Coordinate(20, 9)),
//     std::make_shared<Intersection>(15, Coordinate(24, 9)),
//     std::make_shared<Intersection>(16, Coordinate(28, 9)),
//     std::make_shared<Intersection>(17, Coordinate(2, 14)),
//     std::make_shared<Intersection>(18, Coordinate(10, 14)),
//     std::make_shared<Intersection>(19, Coordinate(20, 14)),
//     std::make_shared<Intersection>(20, Coordinate(24, 14)),
//     std::make_shared<Intersection>(21, Coordinate(28, 14)),
//     std::make_shared<Intersection>(22, Coordinate(2, 19)),
//     std::make_shared<Intersection>(23, Coordinate(10, 19)),
//     std::make_shared<Intersection>(24, Coordinate(20, 19)),
//     std::make_shared<Intersection>(25, Coordinate(24, 19)),
//     std::make_shared<Intersection>(26, Coordinate(28, 19)),
// };

// std::vector<std::shared_ptr<Road>> roads = {
//     std::make_shared<Road>(0, intersections[0], intersections[1], 100, West, East),
//     std::make_shared<Road>(1, intersections[1], intersections[2], 100, West, East),
//     std::make_shared<Road>(2, intersections[2], intersections[3], 100, West, East),
//     std::make_shared<Road>(3, intersections[3], intersections[4], 100, West, East),
//     std::make_shared<Road>(4, intersections[5], intersections[6], 100, West, East),
//     std::make_shared<Road>(5, intersections[6], intersections[7], 100, West, East),
//     std::make_shared<Road>(6, intersections[8], intersections[9], 100, West, East),
//     std::make_shared<Road>(7, intersections[10], intersections[11], 100, West, East),
//     std::make_shared<Road>(8, intersections[11], intersections[12], 100, West, East),
//     std::make_shared<Road>(9, intersections[12], intersections[13], 100, West, East),
//     std::make_shared<Road>(10, intersections[13], intersections[14], 100, West, East),
//     std::make_shared<Road>(11, intersections[14], intersections[15], 100, West, East),
//     std::make_shared<Road>(12, intersections[15], intersections[16], 100, West, East),
//     std::make_shared<Road>(13, intersections[17], intersections[18], 100, West, East),
//     std::make_shared<Road>(14, intersections[19], intersections[20], 100, West, East),
//     std::make_shared<Road>(15, intersections[20], intersections[21], 100, West, East),
//     std::make_shared<Road>(16, intersections[22], intersections[23], 100, West, East),
//     std::make_shared<Road>(17, intersections[23], intersections[24], 100, West, East),
//     std::make_shared<Road>(18, intersections[24], intersections[25], 100, West, East),
//     std::make_shared<Road>(19, intersections[25], intersections[26], 100, West, East),

//     std::make_shared<Road>(20, intersections[0], intersections[10], 100, North, South),
//     std::make_shared<Road>(21, intersections[10], intersections[17], 100, North, South),
//     std::make_shared<Road>(22, intersections[17], intersections[22], 100, North, South),
//     std::make_shared<Road>(23, intersections[1], intersections[11], 100, North, South),
//     std::make_shared<Road>(24, intersections[2], intersections[12], 100, North, South),
//     std::make_shared<Road>(25, intersections[12], intersections[18], 100, North, South),
//     std::make_shared<Road>(26, intersections[18], intersections[23], 100, North, South),
//     std::make_shared<Road>(27, intersections[8], intersections[13], 100, North, South),
//     std::make_shared<Road>(28, intersections[3], intersections[9], 100, North, South),
//     std::make_shared<Road>(29, intersections[4], intersections[5], 100, North, South),
//     std::make_shared<Road>(30, intersections[5], intersections[14], 100, North, South),
//     std::make_shared<Road>(31, intersections[14], intersections[19], 100, North, South),
//     std::make_shared<Road>(32, intersections[19], intersections[24], 100, North, South),
//     std::make_shared<Road>(33, intersections[6], intersections[15], 100, North, South),
//     std::make_shared<Road>(34, intersections[15], intersections[20], 100, North, South),
//     std::make_shared<Road>(35, intersections[20], intersections[25], 100, North, South),
//     std::make_shared<Road>(36, intersections[7], intersections[16], 100, North, South),
//     std::make_shared<Road>(37, intersections[16], intersections[21], 100, North, South),
//     std::make_shared<Road>(38, intersections[21], intersections[26], 100, North, South),
// };

// Updating roads in intersections
// intersections[0]->setRoad(roads[0], East);
// intersections[1]->setRoad(roads[0], West);
// intersections[1]->setRoad(roads[1], East);
// intersections[2]->setRoad(roads[1], West);
// intersections[2]->setRoad(roads[2], East);
// intersections[3]->setRoad(roads[2], West);
// intersections[3]->setRoad(roads[3], East);
// intersections[4]->setRoad(roads[3], West);
// intersections[5]->setRoad(roads[4], East);
// intersections[6]->setRoad(roads[4], West);
// intersections[6]->setRoad(roads[5], East);
// intersections[7]->setRoad(roads[5], West);
// intersections[8]->setRoad(roads[6], East);
// intersections[9]->setRoad(roads[6], West);
// intersections[10]->setRoad(roads[7], East);
// intersections[11]->setRoad(roads[7], West);
// intersections[11]->setRoad(roads[8], East);
// intersections[12]->setRoad(roads[8], West);
// intersections[12]->setRoad(roads[9], East);
// intersections[13]->setRoad(roads[9], West);
// intersections[13]->setRoad(roads[10], East);
// intersections[14]->setRoad(roads[10], West);
// intersections[14]->setRoad(roads[11], East);
// intersections[15]->setRoad(roads[11], West);
// intersections[15]->setRoad(roads[12], East);
// intersections[16]->setRoad(roads[12], West);
// intersections[17]->setRoad(roads[13], East);
// intersections[18]->setRoad(roads[13], West);
// intersections[19]->setRoad(roads[14], East);
// intersections[20]->setRoad(roads[14], West);
// intersections[20]->setRoad(roads[15], East);
// intersections[21]->setRoad(roads[15], West);
// intersections[22]->setRoad(roads[16], East);
// intersections[23]->setRoad(roads[16], West);
// intersections[23]->setRoad(roads[17], East);
// intersections[24]->setRoad(roads[17], West);
// intersections[24]->setRoad(roads[18], East);
// intersections[25]->setRoad(roads[18], West);
// intersections[25]->setRoad(roads[19], East);
// intersections[26]->setRoad(roads[19], West);

// intersections[0]->setRoad(roads[20], South);
// intersections[10]->setRoad(roads[20], North);
// intersections[10]->setRoad(roads[21], South);
// intersections[17]->setRoad(roads[21], North);
// intersections[17]->setRoad(roads[22], South);
// intersections[22]->setRoad(roads[22], North);
// intersections[1]->setRoad(roads[23], South);
// intersections[11]->setRoad(roads[23], North);
// intersections[2]->setRoad(roads[24], South);
// intersections[12]->setRoad(roads[24], North);
// intersections[12]->setRoad(roads[25], South);
// intersections[18]->setRoad(roads[25], North);
// intersections[18]->setRoad(roads[26], South);
// intersections[23]->setRoad(roads[26], North);
// intersections[8]->setRoad(roads[27], South);
// intersections[13]->setRoad(roads[27], North);
// intersections[3]->setRoad(roads[28], South);
// intersections[9]->setRoad(roads[28], North);
// intersections[4]->setRoad(roads[29], South);
// intersections[5]->setRoad(roads[29], North);
// intersections[5]->setRoad(roads[30], South);
// intersections[14]->setRoad(roads[30], North);
// intersections[14]->setRoad(roads[31], South);
// intersections[19]->setRoad(roads[31], North);
// intersections[19]->setRoad(roads[32], South);
// intersections[24]->setRoad(roads[32], North);
// intersections[6]->setRoad(roads[33], South);
// intersections[15]->setRoad(roads[33], North);
// intersections[15]->setRoad(roads[34], South);
// intersections[20]->setRoad(roads[34], North);
// intersections[20]->setRoad(roads[35], South);
// intersections[25]->setRoad(roads[35], North);
// intersections[7]->setRoad(roads[36], South);
// intersections[16]->setRoad(roads[36], North);
// intersections[16]->setRoad(roads[37], South);
// intersections[21]->setRoad(roads[37], North);
// intersections[21]->setRoad(roads[38], South);
// intersections[26]->setRoad(roads[38], North);
// int id = 0;
// std::vector<std::shared_ptr<Building>> buildings = {
//     // BROWN
//     std::make_shared<Building>(id++,Coordinate(5, 5), 1000, 'W'),
//     std::make_shared<Building>(id++,Coordinate(7, 5), 1000, 'W'),
//     // PURPLE
//     std::make_shared<Building>(id++, Coordinate(7, 13), 1000, 'W'),
//     std::make_shared<Building>(id++, Coordinate(5, 15), 1000, 'W'),
//     std::make_shared<Building>(id++, Coordinate(6, 18), 1000, 'W'),
//     // PINK
//     std::make_shared<Building>(id++, Coordinate(13, 6), 1000, 'F'),
//     // CYAN
//     std::make_shared<Building>(id++, Coordinate(18, 8), 1000, 'F'),
//     // YELLOW
//     std::make_shared<Building>(id++, Coordinate(16, 10), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(19, 14), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(21, 5), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(23, 8), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(25, 5), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(27, 8), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(21, 10), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(23, 13), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(25, 10), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(27, 13), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(21, 15), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(23, 18), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(25, 15), 1000, 'H'),
//     std::make_shared<Building>(id++, Coordinate(27, 18), 1000, 'H'),
// };

// std::vector<std::shared_ptr<Person>> people = {
//     std::make_shared<Person>(buildings[20], buildings[10], buildings[0]),
//     std::make_shared<Person>(buildings[15], buildings[5], buildings[7]),
//     std::make_shared<Person>(buildings[9], buildings[2], buildings[14]),
//     std::make_shared<Person>(buildings[14], buildings[2], buildings[20]),
//     std::make_shared<Person>(buildings[17], buildings[4], buildings[9]),
//     std::make_shared<Person>(buildings[18], buildings[8], buildings[3]),
//     std::make_shared<Person>(buildings[13], buildings[9], buildings[4]),
//     std::make_shared<Person>(buildings[11], buildings[1], buildings[9]),

// };