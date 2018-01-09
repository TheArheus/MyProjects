cmake_minimum_required(VERSION 3.9)
project(OpenGL1)

set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL1 main.cpp)

find_package(OpenGL REQUIRED)
find_package(glew REQUIRED)
find_package(glm REQUIRED)
find_package(glfw REQUIRED)

include_directories(OpenGL1 ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIR})
target_link_libraries(OpenGL1 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})