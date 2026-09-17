cmake_minimum_required(VERSION 3.10)
project(LabWork LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# п.3
add_library(util SHARED #STATIC
    util/util.cpp
    util/util.h
)

# п.2
target_include_directories(util PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/util
)

# п.4
add_executable(main main.cpp)
target_link_libraries(main PRIVATE util)
