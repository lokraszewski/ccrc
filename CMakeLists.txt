cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET (CMAKE_C_FLAGS_INIT                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

SET (CMAKE_CXX_FLAGS_INIT                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")



project (cpp-crc)


find_package(benchmark REQUIRED)
find_package (Threads REQUIRED)

set(EXECUTABLE_OUTPUT_PATH "bin")

include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/catch")

set(SOURCE
   ${SOURCE}
)


add_executable (unit_tests ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/unit.cpp)

add_executable (bm ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/bm.cpp)
target_link_libraries(bm benchmark ${CMAKE_THREAD_LIBS_INIT})
