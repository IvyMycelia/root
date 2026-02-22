cmake_minimum_required(VERSION 3.20)
project(ROOT_ENGINE)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.c)
file(GLOB HEADERS include/*.h)

add_executable(ROOT_ENGINE ${SOURCES})

target_include_directories(ROOT_ENGINE PRIVATE src include)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_compile_options(OPTIMIZE_DEPENDENCIES)
target_link_libraries(ROOT_ENGINE PRIVATE glfw OpenGL::GL)
