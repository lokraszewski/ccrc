cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_CXX_STANDARD 17)
project (cpp-crc)


set(EXECUTABLE_OUTPUT_PATH "bin")


#Bring the headers, such as Student.h into the project
include_directories ("${PROJECT_BINARY_DIR}/src")
include_directories ("${PROJECT_BINARY_DIR}/catch")


set(SOURCE
   ${SOURCE}
)


add_executable (unit_tests ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/unit.cpp)
# add_executable(cpp-crc )

