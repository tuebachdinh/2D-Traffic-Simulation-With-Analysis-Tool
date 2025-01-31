#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <memory>
#include "road.hpp"

/**
 * @file globals.h
 * @brief Declares global variables used across the application.
 * 
 * This file declares global variables that are accessible throughout the application. These variables 
 * manage different aspects of the simulation, such as time, rate, coordinates, and roads.
 */

/**
 * @var elapseTime
 * @brief A long variable that tracks the elapsed time in the simulation.
 * 
 * This variable holds the total time that has passed during the simulation. It is used to manage the 
 * progression of time and synchronize various events within the simulation.
 */
extern long elapseTime;

/**
 * @var tick
 * @brief An integer representing the current simulation tick.
 * 
 * This variable indicates the current tick in the simulation. It is typically used to control the 
 * timing of events or actions within the simulation cycle.
 */
extern int tick;

/**
 * @var rate
 * @brief An integer representing the rate of change or speed of the simulation.
 * 
 * This variable controls how fast the simulation progresses. A higher value could indicate a faster 
 * rate of simulation, while a lower value might slow it down.
 */
extern int rate;

/**
 * @var x
 * @brief An integer representing the x-coordinate in the simulation.
 * 
 * This variable is used to store the x-coordinate in the simulation space. It may be used in various 
 * contexts, such as the position of objects or events within the simulation.
 */
extern int x;

/**
 * @var y
 * @brief An integer representing the y-coordinate in the simulation.
 * 
 * This variable stores the y-coordinate in the simulation space, used similarly to the `x` variable 
 * to track the position of objects or events in the simulation.
 */
extern int y;

/**
 * @var globalRoads
 * @brief A vector of shared pointers to `Road` objects used in the simulation.
 * 
 * This variable holds a collection of roads represented by `Road` objects, stored as shared pointers 
 * to ensure proper memory management. It is used throughout the simulation to manage road data and 
 * interact with the roads during the simulation.
 */
extern std::vector<std::shared_ptr<Road>> globalRoads;

const float SCALE = 30.0f;
const float MAP_WIDTH = 30.0f;
const float MAP_HEIGHT = 20.0f;

const int frameWidth = 32;
const int frameHeight = 32;
const int frameCount = 12;
const float frameDuration = 0.1f;

extern bool HIGHLIGHT_MODE;

#endif
