cmake_minimum_required(VERSION 3.9)
project(Vulkan)

set(CMAKE_CXX_STANDARD 11)

add_executable(Vulkan main.cpp Render.cpp Render.h Window.cpp Window.h Window_wnd32.cpp Window_wnd32.h Platform.cpp Platform.h Shared.cpp Shared.h)

find_package(Vulkan)
find_package(SDL2)
find_package(GLFW)

include_directories(Vulkan ${Vulkan_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR})
target_link_libraries(Vulkan ${Vulkan_LIBRARIES} ${GLFW_LIBRARY})