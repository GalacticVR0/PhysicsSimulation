cmake_minimum_required(VERSION 4.4.2)
project(PhysicsSimulation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 CONFIG REQUIRED)

add_executable(PhysicsSimulation
src/main.cpp
src/core.cpp
src/physics.cpp
)

target_link_libraries(PhysicsSimulation PRIVATE SDL3::SDL3)