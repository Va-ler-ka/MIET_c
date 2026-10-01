cmake_minimum_required(VERSION 3.20)
project(lab3_unit_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(NEWTON_BUILD_TESTS "Собирать юнит-тесты" ON)
option(NEWTON_USE_CATCH2  "Собирать тесты на Catch2"     ON)
option(NEWTON_USE_GTEST   "Собирать тесты на GoogleTest" ON)

add_library(numerics_core
    src/bisection_solver.cpp
)
target_include_directories(numerics_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(numerics_demo app/main.cpp)
target_link_libraries(numerics_demo PRIVATE numerics_core)

if(NEWTON_BUILD_TESTS)
    enable_testing()
    include(FetchContent)
    add_subdirectory(tests)
endif()
