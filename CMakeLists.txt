cmake_minimum_required(VERSION 3.10)

project(UFO)

option(HAS_TERMINAL "Show a terminal window for STDOUT/STDERR" ON)

# Set C++ Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required libraries
find_package(CURL REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

set(
    SRC
    src/main.cpp
    src/asset_manager.cpp
    src/camera.cpp
    src/scene_system.cpp
    src/ufo_engine_main.cpp
    src/ufo_pge.cpp
    external/olcPixelGameEngine.cpp
    external/cJSON.c
    src/file.cpp
    src/ufo_json.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

# Link libraries
target_link_libraries(UFO PUBLIC
    CURL::libcurl
    PNG::PNG
    ZLIB::ZLIB
)

# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
target_include_directories(UFO PUBLIC ${OpenGL_INCLUDE_DIRS})
target_link_libraries(UFO PUBLIC OpenGL::GL)

# X11
if(NOT WIN32)
    find_package(X11 REQUIRED)
    if(NOT X11_FOUND)
        message(FATAL_ERROR "X11 not found. Please install X11 development libraries.")
    endif()
    target_include_directories(UFO PUBLIC ${X11_INCLUDE_DIR})
    target_link_libraries(UFO PUBLIC X11::X11)
endif()

# Threads
find_package(Threads REQUIRED)
target_link_libraries(UFO PUBLIC Threads::Threads)

# stdc++fs
target_compile_features(UFO PUBLIC cxx_std_17)