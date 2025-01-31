#ifndef GLOBAL_CPP
#define GLOBAL_CPP

#include "road.hpp"
#include "global.h"

/**
 * @file global.cpp
 * @brief Defines global variables used throughout the application.
 * 
 * This file contains the definition of global variables, such as `globalRoads`, which are used to 
 * store and manage the application's data, specifically roads in this case.
 */

/**
 * @var globalRoads
 * @brief A vector holding shared pointers to `Road` objects.
 * 
 * This global variable stores a collection of `Road` objects. The roads are managed as shared pointers
 * to ensure proper memory management and to allow for multiple references to a single `Road` object.
 * 
 * It is used throughout the application to keep track of roads and perform operations on them.
 */
std::vector<std::shared_ptr<Road>> globalRoads;

#endif
