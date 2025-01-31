#ifndef COORDINATES_H
#define COORDINATES_H

#include <cmath>

/**
 * @struct Coordinate
 * @brief Represents a 2D coordinate with x and y values.
 */
struct Coordinate {
    float x; ///< The x-coordinate value.
    float y; ///< The y-coordinate value.

    /**
     * @brief Constructs a Coordinate with optional x and y values.
     * @param xVal The x-coordinate value (default is 0).
     * @param yVal The y-coordinate value (default is 0).
     */
    Coordinate(float xVal = 0, float yVal = 0) {
        x = xVal;
        y = yVal;
    }
};

/**
 * @brief Compares two Coordinates for equality.
 * 
 * This operator compares two `Coordinate` objects to check if they are equal
 * by calculating the Euclidean distance and checking if it is below a threshold of 0.08.
 * @param lhs The left-hand side `Coordinate`.
 * @param rhs The right-hand side `Coordinate`.
 * @return True if the coordinates are equal, false otherwise.
 */
inline bool operator==(const Coordinate& lhs, const Coordinate& rhs) {
    double dx = rhs.x - lhs.x;
    double dy = rhs.y - lhs.y;
    return std::sqrt(dx * dx + dy * dy) <= 0.08;
}

/**
 * @brief Compares two Coordinates for inequality.
 * 
 * This operator compares two `Coordinate` objects and returns true if they are not equal.
 * @param lhs The left-hand side `Coordinate`.
 * @param rhs The right-hand side `Coordinate`.
 * @return True if the coordinates are not equal, false otherwise.
 */
inline bool operator!=(const Coordinate& lhs, const Coordinate& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Compares two Coordinates to check if the left-hand side is greater.
 * 
 * This operator checks if both the x and y values of the left-hand side `Coordinate`
 * are greater than the corresponding values in the right-hand side `Coordinate`.
 * @param lhs The left-hand side `Coordinate`.
 * @param rhs The right-hand side `Coordinate`.
 * @return True if both x and y of `lhs` are greater than those of `rhs`.
 */
inline bool operator>(const Coordinate& lhs, const Coordinate& rhs) {
    return (lhs.x > rhs.x) && (lhs.y > rhs.y);
}

/**
 * @brief Compares two Coordinates to check if the left-hand side is smaller.
 * 
 * This operator checks if both the x and y values of the left-hand side `Coordinate`
 * are smaller than the corresponding values in the right-hand side `Coordinate`.
 * @param lhs The left-hand side `Coordinate`.
 * @param rhs The right-hand side `Coordinate`.
 * @return True if both x and y of `lhs` are smaller than those of `rhs`.
 */
inline bool operator<(const Coordinate& lhs, const Coordinate& rhs) {
    return (lhs.x < rhs.x) && (lhs.y < rhs.y);
}

/**
 * @brief Multiplies a `Coordinate` by an integer scalar.
 * 
 * This operator multiplies both the x and y components of the `Coordinate` by the given integer value.
 * @param lhs The `Coordinate` to be multiplied.
 * @param rhs The integer scalar by which the coordinate is multiplied.
 * @return A new `Coordinate` with the x and y components multiplied by `rhs`.
 */
inline Coordinate operator*(const Coordinate& lhs, const int rhs) {
    return {lhs.x * rhs, lhs.y * rhs};
}

#endif
