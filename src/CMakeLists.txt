# ===========================================================================
#                  SeqAn - The Library for Sequence Analysis
# ===========================================================================
# File: /apps/stellar/CMakeLists.txt
#
# CMakeLists.txt file for STELLAR.
# ===========================================================================

cmake_minimum_required (VERSION 3.8)
message (STATUS "Configuring apps/stellar")

set (SEQAN_APP_VERSION "${PROJECT_VERSION}")

# ----------------------------------------------------------------------------
# Setup SeqAn 2
# ----------------------------------------------------------------------------

find_path (STELLAR_ROOT_DIR NAMES src/stellar.cpp HINTS "${CMAKE_CURRENT_LIST_DIR}/..")

# needed for find_package(SeqAn) (finding header files)
find_path (SEQAN_INCLUDE_PATH NAMES seqan/version.h HINTS "${STELLAR_ROOT_DIR}/lib/seqan/include")

find_path (SEQAN_BUILD_SYSTEM_CMAKE_DIR NAMES SeqAnBuildSystem.cmake HINTS "${STELLAR_ROOT_DIR}/lib/seqan/util/cmake/")
if (EXISTS "${SEQAN_BUILD_SYSTEM_CMAKE_DIR}")
    # needed for include(SeqAnBuildSystem)
    set (CMAKE_MODULE_PATH "${SEQAN_BUILD_SYSTEM_CMAKE_DIR}" "${CMAKE_MODULE_PATH}")
    # needed for find_package (SeqAn) (finding seqan-config.cmake)
    set (CMAKE_PREFIX_PATH "${SEQAN_BUILD_SYSTEM_CMAKE_DIR}" "${CMAKE_PREFIX_PATH}")
endif ()

add_custom_target (seqan_library) # place-holder needed for SeqAnBuildSystem
include (SeqAnBuildSystem) # for seqan_setup_install_vars, seqan_add_app_test
enable_testing () # enable app tests

find_path (SEQAN_APP_TEST_PYTHON_LIB_DIR NAMES seqan/app_tests.py HINTS "${STELLAR_ROOT_DIR}/lib/seqan/util/py_lib/")
macro (seqan_add_app_test APP_NAME)
    find_package (Python3)
    if (Python3_Interpreter_FOUND)
      add_test (NAME app_test_${APP_NAME}${ARGV1}
                COMMAND ${CMAKE_COMMAND} -E env
                            PYTHONPATH=${SEQAN_APP_TEST_PYTHON_LIB_DIR} # make seqan/app_tests.py available
                        ${Python3_EXECUTABLE}
                        ${STELLAR_ROOT_DIR}/tests/run_tests${ARGV1}.py
                        ${STELLAR_ROOT_DIR} ${CMAKE_BINARY_DIR})
    endif (Python3_Interpreter_FOUND)
endmacro (seqan_add_app_test APP_NAME)

# ----------------------------------------------------------------------------
# Setup SeqAn 3
# ----------------------------------------------------------------------------

# A interface to reuse common properties.
# You can add more external include paths of other projects that are needed for your project.
add_library ("${PROJECT_NAME}_interface" INTERFACE)
target_link_libraries ("${PROJECT_NAME}_interface" INTERFACE seqan3::seqan3)
target_include_directories ("${PROJECT_NAME}_interface" INTERFACE ../include)
target_compile_options ("${PROJECT_NAME}_interface" INTERFACE "-pedantic" "-Wall" "-Wextra")

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Search SeqAn and select dependencies.
if (NOT "${SEQAN_BUILD_SYSTEM}" STREQUAL "DEVELOP")
    find_package (SeqAn CONFIG REQUIRED)
endif ()

# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

# Add include directories.
include_directories (${SEQAN_INCLUDE_DIRS})

# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# Add definitions set by the build system.
add_definitions (-DSEQAN_APP_VERSION="${SEQAN_APP_VERSION}")
add_definitions (-DSEQAN_REVISION="${SEQAN_REVISION}")
add_definitions (-DSEQAN_DATE="${SEQAN_DATE}")

# Update the list of file names below if you add source files to your application.
add_executable (stellar stellar.cpp
                       stellar.h
                       stellar_extension.h
                       stellar_output.h
                       stellar_types.h)

# Add dependencies found by find_package (SeqAn).
target_link_libraries (stellar ${SEQAN_LIBRARIES})

# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

# ----------------------------------------------------------------------------
# Installation
# ----------------------------------------------------------------------------

# Set variables for installing, depending on the selected build type.
if (NOT SEQAN_PREFIX_SHARE_DOC)
  seqan_setup_install_vars (stellar)
endif (NOT SEQAN_PREFIX_SHARE_DOC)

# Install stellar in ${PREFIX}/bin directory
install (TARGETS stellar
         DESTINATION ${CMAKE_INSTALL_BINDIR})

# Install non-binary files for the package to "." for app builds and
# ${PREFIX}/share/doc/stellar for SeqAn release builds.
install (FILES LICENSE
               README
         DESTINATION ${SEQAN_PREFIX_SHARE_DOC})
install (FILES example/NC_001474.fasta
               example/NC_001477.fasta
               example/reads.fasta
         DESTINATION ${SEQAN_PREFIX_SHARE_DOC}/example)

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

# ----------------------------------------------------------------------------
# CPack Install
# ----------------------------------------------------------------------------

if (SEQAN_BUILD_SYSTEM STREQUAL "APP:stellar")
  set (CPACK_PACKAGE_NAME "stellar")
  set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "STELLAR - SwifT Exact LocaL AligneR")
  set (CPACK_DEBIAN_PACKAGE_MAINTAINER "David Weese <david.weese@fu-berlin.de>")
  set (CPACK_PACKAGE_VENDOR "SeqAn Team, FU Berlin")

  seqan_configure_cpack_app (stellar "Stellar")
endif (SEQAN_BUILD_SYSTEM STREQUAL "APP:stellar")
