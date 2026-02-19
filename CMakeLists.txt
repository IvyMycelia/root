cmake_minimum_required(VERSION 3.20)
project(ROOT_ENGINE)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS include/*.h)

add_executable(ROOT_ENGINE ${SOURCES} ${HEADERS})

target_include_directories(ROOT_ENGINE PRIVATE src include)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(ROOT_ENGINE PRIVATE glfw OpenGL::GL)
