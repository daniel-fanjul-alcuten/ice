# Locate the Google C++ Mocking Framework.
#
# Defines the following variables:
#
#   GTEST_FOUND - Found the Google Mocking framework
#   GTEST_INCLUDE_DIRS - Include directories
#
# Also defines the library variables below as normal
# variables.  These contain debug/optimized keywords when
# a debugging library is found.
#
#   GMOCK_BOTH_LIBRARIES - Both libgmock & libgmock-main
#   GMOCK_LIBRARIES - libgmock
#   GMOCK_MAIN_LIBRARIES - libgmock-main
#
# Accepts the following variables as input:
#
#   GMOCK_ROOT - (as a CMake or environment variable)
#                The root directory of the gmock install prefix
#
#   GMOCK_MSVC_SEARCH - If compiling with MSVC, this variable can be set to
#                       "MD" or "MT" to enable searching a GMock build tree
#                       (defaults: "MD")
#
#-----------------------

function(_gmock_append_debugs _endvar _library)
    if(${_library} AND ${_library}_DEBUG)
        set(_output optimized ${${_library}} debug ${${_library}_DEBUG})
    else()
        set(_output ${${_library}})
    endif()
    set(${_endvar} ${_output} PARENT_SCOPE)
    message(STATUS "${${_library}}")
endfunction()

function(_gmock_find_library _name)
    find_library(${_name}
        NAMES ${ARGN}
        HINTS
            $ENV{GMOCK_ROOT}
            ${GMOCK_ROOT}
        PATH_SUFFIXES ${_gmock_libpath_suffixes}
    )
    mark_as_advanced(${_name})
endfunction()

#check for dependency to GTest
set (FIND_GTEST_ARGS GTest)
if (GMock_FIND_QUIETLY)
    set (FIND_GTEST_ARGS ${FIND_GTEST_ARGS} QUIET)
endif ()
if (GMock_FIND_REQUIRED)
    set (FIND_GTEST_ARGS ${FIND_GTEST_ARGS} REQUIRED)
endif ()
find_package(${FIND_GTEST_ARGS})

if (GTEST_FOUND)
    if(NOT DEFINED GMOCK_MSVC_SEARCH)
        set(GMOCK_MSVC_SEARCH MD)
    endif()

    set(_gmock_libpath_suffixes lib)
    if(MSVC)
        if(GMOCK_MSVC_SEARCH STREQUAL "MD")
            list(APPEND _gmock_libpath_suffixes
                msvc/gmock-md/Debug
                msvc/gmock-md/Release)
        elseif(GMOCK_MSVC_SEARCH STREQUAL "MT")
            list(APPEND _gmock_libpath_suffixes
                msvc/gmock/Debug
                msvc/gmock/Release)
        endif()
    endif()


    find_path(GMOCK_INCLUDE_DIR gmock/gmock.h
        HINTS
            $ENV{GMOCK_ROOT}/include
            ${GMOCK_ROOT}/include
    )
    mark_as_advanced(GMOCK_INCLUDE_DIR)

    if(MSVC AND GMOCK_MSVC_SEARCH STREQUAL "MD")
        # The provided /MD project files for Google Mock add -md suffixes to the
        # library names.
        _gmock_find_library(GMOCK_LIBRARY            gmock-md  gmock)
        _gmock_find_library(GMOCK_LIBRARY_DEBUG      gmock-mdd gmockd)
        _gmock_find_library(GMOCK_MAIN_LIBRARY       gmock_main-md  gmock_main)
        _gmock_find_library(GMOCK_MAIN_LIBRARY_DEBUG gmock_main-mdd gmock_maind)
    else()
        _gmock_find_library(GMOCK_LIBRARY            gmock)
        _gmock_find_library(GMOCK_LIBRARY_DEBUG      gmockd)
        _gmock_find_library(GMOCK_MAIN_LIBRARY       gmock_main)
        _gmock_find_library(GMOCK_MAIN_LIBRARY_DEBUG gmock_maind)
    endif()

    include(FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMock DEFAULT_MSG GMOCK_LIBRARY GMOCK_INCLUDE_DIR GMOCK_MAIN_LIBRARY)

    if(GMOCK_FOUND)
        set(GMOCK_INCLUDE_DIRS ${GMOCK_INCLUDE_DIR})
        _gmock_append_debugs(GMOCK_LIBRARIES      GMOCK_LIBRARY)
        _gmock_append_debugs(GMOCK_MAIN_LIBRARIES GMOCK_MAIN_LIBRARY)
        set(GMOCK_BOTH_LIBRARIES ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES})
    endif()
else()
    message(STATUS "GMock depends on GTest library. To use GMock make sure you have GTest installed.")
endif()
