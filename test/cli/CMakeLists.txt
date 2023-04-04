cmake_minimum_required (VERSION 3.16.9)

add_custom_target (cli_test ALL)
add_dependencies (cli_test stellar)

# ----------------------------------------------------------------------------
# Setup SeqAn 2 Tests
# ----------------------------------------------------------------------------
find_path (SEQAN_APP_TEST_PYTHON_LIB_DIR NAMES seqan/app_tests.py HINTS "${STELLAR_ROOT_DIR}/lib/seqan/util/py_lib/")
macro (stellar_cli_test APP_NAME alphabet database_strand output_extension)
    find_package (PythonInterp 3)
    if (PYTHONINTERP_FOUND)
      add_test (NAME "cli/${APP_NAME}/${alphabet}/${database_strand}/${output_extension}"
                COMMAND ${CMAKE_COMMAND} -E env
                            PYTHONPATH=${SEQAN_APP_TEST_PYTHON_LIB_DIR} # make seqan/app_tests.py available
                        ${PYTHON_EXECUTABLE}
                        ${STELLAR_ROOT_DIR}/test/cli/run_tests.py
                        ${STELLAR_ROOT_DIR} ${CMAKE_BINARY_DIR}
                        --alphabets "${alphabet}"
                        --database-strands "${database_strand}"
                        --output-extensions "${output_extension}"
                )
    endif (PYTHONINTERP_FOUND)
endmacro (stellar_cli_test APP_NAME)

# ----------------------------------------------------------------------------
# App Test
# ----------------------------------------------------------------------------

foreach(alphabet dna dna5 protein char)
    foreach(database_strand forward reverse both)
        foreach(output_extensions gff txt)
            stellar_cli_test (stellar "${alphabet}" "${database_strand}" "${output_extensions}")
        endforeach()
    endforeach()
endforeach()


# ----------------------------------------------------------------------------
# Setup Common Tool Description for Generic Workflow Nodes
# ----------------------------------------------------------------------------

# Include executable stellar in CTD structure.
set (SEQAN_CTD_EXECUTABLES ${SEQAN_CTD_EXECUTABLES} stellar CACHE INTERNAL "")

#Add test to check correct ctd generation.
seqan_add_ctd_test (stellar)

# Prefiltered Stellar CLI tests
macro (add_cli_test test_filename)
    add_app_test (${test_filename})

    seqan3_test_component (target "${test_filename}" TARGET_NAME)
    add_dependencies (cli_test ${target})
    add_dependencies (${target} "${PROJECT_NAME}")
endmacro ()

add_cli_test (stellar_test.cpp)
target_use_datasources (stellar_test FILES ref.fasta)
target_use_datasources (stellar_test FILES multi_seq_ref.fasta)
target_use_datasources (stellar_test FILES query_e0.05.fasta)

target_use_datasources (stellar_test FILES 0_0_400.gff)
target_use_datasources (stellar_test FILES 0_500_643.gff)
target_use_datasources (stellar_test FILES 0_600_763.gff)

target_use_datasources (stellar_test FILES 0_0_400.stdout)
target_use_datasources (stellar_test FILES 0_500_643.stdout)
target_use_datasources (stellar_test FILES 0_600_763.stdout)

target_use_datasources (stellar_test FILES 1_.gff)
target_use_datasources (stellar_test FILES 0_1_.gff)
target_use_datasources (stellar_test FILES 1_2_.gff)
target_use_datasources (stellar_test FILES 0_1_2_.gff)

target_use_datasources (stellar_test FILES 1_.stdout)
target_use_datasources (stellar_test FILES 0_1_.stdout)
target_use_datasources (stellar_test FILES 1_2_.stdout)
target_use_datasources (stellar_test FILES 0_1_2_.stdout)
