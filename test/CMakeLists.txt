file( GLOB TEST_SOURCES *_test.cpp  )

foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    message("Adding test: ${test_source} : ${test_name}")

    add_executable(${test_name} ${test_source} )

    set_target_properties(${test_name}
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
    )

    target_link_libraries(${test_name}
        ${PROJECT_NAME}
        Catch2::Catch2
    )


endforeach()




