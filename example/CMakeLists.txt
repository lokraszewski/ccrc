find_package(spdlog)

add_executable(${PROJECT_NAME}_example
  ${PROJECT_NAME}_example.cpp )

target_include_directories(${PROJECT_NAME}_example
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}_example
  ${PROJECT_NAME}
  spdlog::spdlog
)

set_target_properties(${PROJECT_NAME}_example
  PROPERTIES
    CXX_STANDARD 17
)
