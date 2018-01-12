cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_CXX_STANDARD 17)

project (cpp-crc)




#Bring the headers, such as Student.h into the project
include_directories ("${PROJECT_BINARY_DIR}/src")
include_directories ("${PROJECT_BINARY_DIR}/catch")


set(SOURCE
   ${SOURCE}
   # ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp-crc.cpp
)


add_executable (cpp-test0 ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/test0/main.cpp)
# add_executable(cpp-crc )

