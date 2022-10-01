cmake_Minimum_required(VERSION 3.11.0)
project(cherno_gl)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
# find_package(glm REQUIRED)


add_library(debugger src/debugger.cpp include/debugger.hpp)
add_library(vertexBuffer src/vertexBuffer.cpp include/vertexBuffer.hpp)
add_library(indexBuffer src/indexBuffer.cpp include/indexBuffer.hpp)
add_library(vertexArray src/vertexArray.cpp include/vertexArray.hpp)
add_library(shader src/shader.cpp include/shader.hpp)

add_library(renderer src/renderer.cpp include/renderer.hpp)

add_executable(objectRender_noClasses src/objectRender_noClasses.cpp)
target_link_libraries(objectRender_noClasses glfw OpenGL::GL GLEW)

add_executable(objectRender src/objectRender.cpp)
target_link_libraries(objectRender glfw OpenGL::GL GLEW debugger vertexBuffer indexBuffer vertexArray shader renderer)