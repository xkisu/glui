cmake_minimum_required(VERSION 3.9)
project(glui)

set(CMAKE_CXX_STANDARD 11)

add_executable(glui src/main.cpp src/config.h src/graphics/window.cpp src/graphics/window.h src/graphics/shader.h src/graphics/shader.cpp src/graphics/uniform_container.h src/graphics/uniform_container.cpp src/ui/ui_element.cpp src/ui/ui_element.h src/graphics/camera.cpp src/graphics/camera.h src/util/color.h)

include_directories(src/)

# GLEW

include_directories(src/external/glew/include)
add_subdirectory(src/external/glew/build/cmake)

add_definitions(-DGLEW_STATIC)
target_link_libraries(glui glew)

# GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(src/external/glfw)
include_directories(src/external/glfw/include)
target_link_libraries(glui glfw)

# GLM

include_directories(src/external/glm/)

# Physfs

add_definitions(-DPHYSFS_BUILD_STATIC)
remove_definitions(-DPHYSFS_BUILD_SHARED)
add_subdirectory(src/external/physfs)
include_directories(src/external/physfs/src)

target_link_libraries(glui physfs-static)

# shaders

add_custom_command(TARGET glui PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:glui>/shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:glui>/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:glui>/shaders)