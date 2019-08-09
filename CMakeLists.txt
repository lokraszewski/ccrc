cmake_minimum_required(VERSION 3.9)

include(ExternalProject)

project(ccrc
  VERSION 1.3.3
  LANGUAGES CXX
  )


# Check out Git submodules.
message(STATUS "Checking for submodules")
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.gitmodules")
    message(STATUS "Updating submodules ")
    execute_process (COMMAND git submodule update --init --recursive
     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

option(BUILD_ALL "Enable building everything" OFF)
option(BUILD_TEST "Enable building tests" OFF)
option(BUILD_EXAMPLE "Enable building example app." OFF)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options("-Wall"
    "-Wextra"
    "-Werror"
    "-Wfatal-errors"
    "$<$<CONFIG:RELEASE>:-O3>")

# Workaround for Catch2 not working with clang.
add_definitions(
  -DCATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS

  )

add_subdirectory(${PROJECT_NAME})

if(BUILD_TEST OR BUILD_ALL)
    add_subdirectory(third_party/catch2)
    add_subdirectory(test)
endif()

if(BUILD_EXAMPLE OR BUILD_ALL)
    add_subdirectory(third_party/spdlog)
    add_subdirectory(example)
endif()
