cmake_minimum_required(VERSION 3.10)

project(Engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Engine
    Main.cpp
)

find_package(glfw3 REQUIRED)

target_link_libraries(Engine
    glfw
    GL
)