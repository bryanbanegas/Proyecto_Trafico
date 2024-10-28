cmake_minimum_required(VERSION 3.5)
project("GPS")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_mixer_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp vehiculo.cpp grafo.cpp) 

target_link_libraries(${PROJECT_NAME} 
    SDL2::SDL2
)