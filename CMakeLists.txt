cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")


project (cpp-crc)




#Bring the headers, such as Student.h into the project
# include_directories(CMAKE_SOURCE_DIR)
include_directories ("${PROJECT_BINARY_DIR}")

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
# file(GLOB HEADERS "*h")
file(GLOB SOURCES "*.cpp")

add_executable(cpp-crc ${SOURCES})

