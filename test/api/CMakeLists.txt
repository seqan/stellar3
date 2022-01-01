cmake_minimum_required (VERSION 3.8)

add_custom_target (api_test ALL)

# needed for add_app_test
add_library ("${PROJECT_NAME}_lib" INTERFACE)
target_link_libraries (${PROJECT_NAME}_lib INTERFACE "${PROJECT_NAME}_interface")

macro (add_api_test test_filename)
    add_app_test (${test_filename})

    seqan3_test_component (target "${test_filename}" TARGET_NAME)
    add_dependencies (api_test ${target})
endmacro ()
