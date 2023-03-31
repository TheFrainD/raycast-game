cmake_minimum_required(VERSION 3.24)
project(raycaster)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/W4")
    target_compile_options(${PROJECT_NAME} PRIVATE "/WX")
    target_compile_options(${PROJECT_NAME} PRIVATE "/wd4100")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-variable)
endif()
