cmake_minimum_required(VERSION 3.26)

project(Basic_Software_Rasterizer_Raylib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Basic_Software_Rasterizer_Raylib
    src/main.cpp
)

# Find raylib from vcpkg
find_package(raylib CONFIG REQUIRED)

# Find glfw3 from vcpkg
find_package(glfw3 CONFIG REQUIRED)

# Link it
target_link_libraries(Basic_Software_Rasterizer_Raylib
    PRIVATE
    raylib
    glfw
)