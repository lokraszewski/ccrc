add_executable(${PROJECT_NAME}_test
  ${PROJECT_NAME}_test.cpp )

# target_include_directories(${PROJECT_NAME}_test
#     PUBLIC
#         $<INSTALL_INTERFACE:include>
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
# )

target_link_libraries(${PROJECT_NAME}_test
  ${PROJECT_NAME}
  CONAN_PKG::catch2
)

set_target_properties(${PROJECT_NAME}_test
  PROPERTIES
    CXX_STANDARD 17
)
