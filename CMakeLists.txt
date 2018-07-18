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
add_subdirectory(pybind)

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

