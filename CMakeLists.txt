cmake_minimum_required(VERSION 3.6)

# Global option #
#################

# Wyrm #
##############

project(wyrm VERSION 0.1 LANGUAGES CXX)

add_library(wyrm INTERFACE)

target_compile_features(wyrm INTERFACE cxx_std_14)

target_include_directories(wyrm INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>  
    $<INSTALL_INTERFACE:inc>
)

# Add pybind
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.4")
    include(FetchContent)
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG        v2.2.3
    )
    
    FetchContent_GetProperties(pybind11)
    if(NOT pybind11_POPULATED)
        FetchContent_Populate(pybind11)
        add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
    endif()
    
else()
    
    add_subdirectory(pybind)

endif()

target_link_libraries(wyrm INTERFACE pybind11::module)

########################################################################
#
# Google Test.
#
# The tests are not built by default.  To build them, set the
# gtest_build_tests option to ON.  You can do it by running ccmake
# or specifying the -Dgtest_build_tests=ON flag when running cmake.

if (gtest_build_tests)
  # This must be set in the root directory for the tests to be run by
  # 'make test' or ctest.
  enable_testing()
  add_subdirectory(test)
endif()

########################################################################
#
# Example.
#
# The examples are not built by default.  To build them, set the
# build_examples option to ON.  You can do it by running ccmake
# or specifying the -Dbuild_examples=ON flag when running cmake.

if(build_examples)
    add_subdirectory(example/SimpleWrap)
endif()

# Install #
###########

# install(TARGETS wyrm EXPORT wyrm_targets)

# install(DIRECTORY inc/ma DESTINATION include)

# install(EXPORT wyrm_targets DESTINATION lib/cmake/wyrm)

# export(TARGETS wyrm FILE wyrm_targets.cmake)

