cmake_minimum_required(VERSION 3.30)

option(KORI_BUILD_EXAMPLES "Build the examples" ON)

project(kori LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(kori INTERFACE)

target_include_directories(kori INTERFACE ./include/)

if (KORI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
