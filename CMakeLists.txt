cmake_minimum_required(VERSION 3.5)
project("GPS")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

find_package(SDL2 REQUIRED)

include_directories(/usr/include/SDL2)
include_directories(/usr/include(/SDL2_ttf))

add_executable(${PROJECT_NAME} main.cpp vehiculo.cpp grafo.cpp arbol.cpp) 

target_link_libraries(${PROJECT_NAME} 
    SDL2::SDL2
    /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
)