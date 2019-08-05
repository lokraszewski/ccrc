
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

target_compile_features(${PROJECT_NAME}_example PRIVATE cxx_std_17)

