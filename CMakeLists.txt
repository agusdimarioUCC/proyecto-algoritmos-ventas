cmake_minimum_required(VERSION 3.15)
project(proyecto_algoritmos_ventas)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add all source files
add_executable(proyecto_algoritmos_ventas
        src/main.cpp)
