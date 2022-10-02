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
add_library(image_loader src/stb_image.cpp include/vendor/stb_image/stb_image.h)

add_library(texture src/texture.cpp include/texture.hpp)
target_link_libraries(texture image_loader)

add_executable(renderFlashingObject_noClasses src/APPS/renderFlashingObject_noClasses.cpp)
target_link_libraries(renderFlashingObject_noClasses glfw OpenGL::GL GLEW)

add_executable(renderFlashingObject src/APPS/renderFlashingObject.cpp)
target_link_libraries(renderFlashingObject glfw OpenGL::GL GLEW debugger vertexBuffer indexBuffer vertexArray shader renderer)

add_executable(renderObject_texture src/APPS/renderObject_texture.cpp)
target_link_libraries(renderObject_texture glfw OpenGL::GL GLEW debugger vertexBuffer indexBuffer vertexArray shader renderer texture)