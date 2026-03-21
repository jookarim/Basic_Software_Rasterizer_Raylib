cmake_minimum_required(VERSION 3.26)

project(Basic_Software_Rasterizer_Raylib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Basic_Software_Rasterizer_Raylib
    src/main.cpp
)

# ---------------- raylib ----------------
find_package(raylib CONFIG REQUIRED)


# ---------------- ImGui ----------------
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_demo.cpp
)

target_include_directories(imgui PUBLIC
    external/imgui
)

# ---------------- rlImGui ----------------
add_library(rlImGui STATIC
    external/rlImGui/rlImGui.cpp
)

target_include_directories(rlImGui PUBLIC
    external/imgui
    external/rlImGui
)

target_link_libraries(rlImGui
    PUBLIC
    imgui
    raylib
)

# ---------------- Final Link ----------------
target_link_libraries(Basic_Software_Rasterizer_Raylib
    PRIVATE
    raylib
    imgui
    rlImGui
)