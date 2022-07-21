cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "primer")

project(${PROJECT_NAME} LANGUAGES CXX)
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)
option(MYLIB_COVERAGE "Включить измерение покрытия кода тестами" OFF)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Свойства для статического подключения бибилотек
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -fpermissive")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(
    GLOB sources
    ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/**/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h
    D:/projects/debugMy/mydebug.h
    D:/projects/debugMy/mydebug.cpp
)
add_executable(${PROJECT_NAME} ${sources})

#target_link_options(${PROJECT_NAME} PRIVATE -mwindows -municode)

