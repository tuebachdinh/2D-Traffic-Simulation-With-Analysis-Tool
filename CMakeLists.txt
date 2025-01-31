cmake_minimum_required(VERSION 3.10)

# Project name
project(TrafficSimulator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the SFML installation path
set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found. Please check your SFML installation at /opt/homebrew/opt/sfml.")
endif()

# Add executable and include all .cpp files
add_executable(TrafficSimulator
    src/main.cpp
    src/building.cpp
    src/car.cpp
    src/city.cpp
    src/intersection.cpp
    src/person.cpp
    src/road.cpp
    src/entity.cpp
    src/bus.cpp
    src/global.cpp
)

# Include SFML headers
target_include_directories(TrafficSimulator PRIVATE ${SFML_INCLUDE_DIR})

# Link SFML libraries
target_link_libraries(TrafficSimulator sfml-graphics sfml-window sfml-system)

# Copy assets folder to the build directory
add_custom_command(
    TARGET TrafficSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TrafficSimulator>/assets
)

# Print a message to confirm the asset copy process
message(STATUS "Assets folder will be copied to the build directory.")
message(STATUS "SFML found at: ${SFML_DIR}")

# Add Google Test for unit testing
# Enable testing
enable_testing()

# Download and unpack Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add a test executable
message(STATUS "Adding TrafficSimulatorTests target")
add_executable(TrafficSimulatorTests
    tests/tests.cpp
)

# Include directories for tests
target_include_directories(TrafficSimulatorTests PRIVATE src)

# Link Google Test and other dependencies
target_link_libraries(TrafficSimulatorTests gtest gtest_main sfml-graphics sfml-window sfml-system)

# Add tests
include(GoogleTest)
gtest_discover_tests(TrafficSimulatorTests)