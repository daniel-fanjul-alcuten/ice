cmake_minimum_required (VERSION 2.6)
project (ice)
set (ice_VERSION_MAJOR 1)
set (ice_VERSION_MINOR 0)
#SET(CMAKE_BUILD_TYPE release)
 SET(CMAKE_BUILD_TYPE Debug)

# add modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/cmake")

#include coverage
INCLUDE(CodeCoverage)

set(Boost_USE_STATIC_LIBS ON)
set(BUILD_SHARED_LIBS FALSE)
find_package(Boost REQUIRED COMPONENTS thread)

# configure a header file to pass some of the CMake settings
# to the source code
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
configure_file (
  "${PROJECT_SOURCE_DIR}/ice_config.h.in"
  "${PROJECT_BINARY_DIR}/ice_config.h"
  )

include_directories("${PROJECT_BINARY_DIR}")

################################
# GTest and GMock
################################
enable_testing()
set(GMOCK_ROOT "lib/gmock-1.6.0/")
set(GTEST_ROOT "${GMOCK_ROOT}/gtest/")
find_package(GMock REQUIRED)

################################
# Tests
################################
# Add test file
file(GLOB TestFiles **/*_test.cc)

set(iceSources lib/libgflags.a)

file(GLOB TagSources **/*cc **/*h)

set(SourceFiles ${iceSources})

SETUP_TARGET_FOR_COVERAGE(cov runTests doc/coverage)
add_executable(runTests ${SourceFiles} ${TestFiles})
# Link test executable against gtest & gtest_main
add_test(runTests runUnitTests)

#set doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                 ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE}
                    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation..." VERBATIM
  )
endif(DOXYGEN_FOUND)

# add executable
add_executable(ice ice.cc ${SourceFiles})

# link libs
include_directories(${Boost_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS}
  ${GMOCK_INCLUDE_DIRS})

target_link_libraries(Fice libgflags.a dl ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES})

target_link_libraries(runTests libgflags.a dl ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

# ctags exuberant
add_custom_command (TARGET ice POST_BUILD COMMAND
  ctags --sort=foldcase --c++-kinds=+p --fields=+iaS --extra=+q -f tags
  ${TagSources}
  COMMENT "Creating tags" VERBATIM)
