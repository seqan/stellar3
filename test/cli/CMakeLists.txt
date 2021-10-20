cmake_minimum_required (VERSION 3.8)

add_custom_target (cli_test ALL)

# ----------------------------------------------------------------------------
# Setup SeqAn 2 Tests
# ----------------------------------------------------------------------------
find_path (SEQAN_APP_TEST_PYTHON_LIB_DIR NAMES seqan/app_tests.py HINTS "${STELLAR_ROOT_DIR}/lib/seqan/util/py_lib/")
macro (seqan_add_app_test APP_NAME)
    find_package (Python3)
    if (Python3_Interpreter_FOUND)
      add_test (NAME app_test_${APP_NAME}${ARGV1}
                COMMAND ${CMAKE_COMMAND} -E env
                            PYTHONPATH=${SEQAN_APP_TEST_PYTHON_LIB_DIR} # make seqan/app_tests.py available
                        ${Python3_EXECUTABLE}
                        ${STELLAR_ROOT_DIR}/test/cli/run_tests${ARGV1}.py
                        ${STELLAR_ROOT_DIR} ${CMAKE_BINARY_DIR})
    endif (Python3_Interpreter_FOUND)
endmacro (seqan_add_app_test APP_NAME)

# ----------------------------------------------------------------------------
# App Test
# ----------------------------------------------------------------------------

seqan_add_app_test (stellar)

# ----------------------------------------------------------------------------
# Setup Common Tool Description for Generic Workflow Nodes
# ----------------------------------------------------------------------------

# Include executable stellar in CTD structure.
set (SEQAN_CTD_EXECUTABLES ${SEQAN_CTD_EXECUTABLES} stellar CACHE INTERNAL "")

#Add test to check correct ctd generation.
seqan_add_ctd_test (stellar)
