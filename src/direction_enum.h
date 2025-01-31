#ifndef DIRECTIONS_H
#define DIRECTIONS_H

/**
 * @enum Direction
 * @brief Represents the four cardinal directions.
 *
 * This enum defines the four primary compass directions: North, East, South, and West.
 */
enum Direction {
    North, ///< Represents the North direction.
    East,  ///< Represents the East direction.
    South, ///< Represents the South direction.
    West   ///< Represents the West direction.
};

/**
 * @brief Gets the opposite direction of the given direction.
 * 
 * This operator returns the opposite of the specified direction:
 * - North -> South
 * - East -> West
 * - South -> North
 * - West -> East
 * 
 * @param other The `Direction` to find the opposite of.
 * @return The opposite `Direction`.
 */
inline Direction operator!(const Direction& other) {
    switch (other) {
        case North: return South;
        case East:  return West;
        case South: return North;
        default: return East; 
    }
}

#endif
