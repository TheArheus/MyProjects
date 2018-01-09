cmake_minimum_required(VERSION 3.9)
project(SDL)

set(CMAKE_CXX_STANDARD 11)
add_executable(SDL main.cpp Display.cpp Display.h Shader.cpp Shader.h Mesh.cpp Mesh.h)
# Display.cpp Display.h Shader.cpp Shader.h Mesh.cpp Mesh.h

find_package(GLEW)
find_package(OpenGL)
find_package(GLM)
find_package(SDL2)

include_directories(SDL ${GLEW_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${LUA_INCLUDE_DIRS})
target_link_libraries(SDL ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${SDL2_LIBRARY} ${LUA_LIBRARIES})