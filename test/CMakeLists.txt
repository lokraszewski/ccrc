add_executable(${PROJECT_NAME}_test
  ${PROJECT_NAME}_test.cpp )


target_link_libraries(${PROJECT_NAME}_test
  ${PROJECT_NAME}
  catch2::catch2
)

set_target_properties(${PROJECT_NAME}_test
  PROPERTIES
    CXX_STANDARD 17
)
