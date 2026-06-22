cmake_minimum_required(VERSION 3.16)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Engine
    src/Main.cpp
    glad.c
)


find_package(glfw3 REQUIRED)


target_include_directories(Engine PRIVATE
    Libraries/include
)

target_link_libraries(Engine
    glfw
    GL
)
