cmake_minimum_required(VERSION 3.9)

include(ExternalProject)

project(crc
  VERSION 1.0.0
  LANGUAGES CXX
  )

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

option(BUILD_TEST "Enable building tests" OFF)
# option(BUILD_BENCHMARK "Enable automatic benchmark" OFF)



set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")

# Workaround for Catch2 not working with clang.
add_definitions(
  -DCATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS
)

find_package(catch2)

add_subdirectory(${PROJECT_NAME})

if(BUILD_TEST)
add_subdirectory(test)
endif(BUILD_TEST)

# if(BUILD_BENCHMARK)
# add_subdirectory(benchmark)
# endif(BUILD_BENCHMARK)
