cmake_minimum_required(VERSION 3.6)

# Global option #
#################

set (CMAKE_CXX_STANDARD 14)

# Pybind11Util #
##############

project(Pybind11Util VERSION 0.1 LANGUAGES CXX)

add_library(Pybind11Util INTERFACE)

target_include_directories(Pybind11Util INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>  
    $<INSTALL_INTERFACE:inc>
)

# Add pybind
add_subdirectory(pybind)

target_link_libraries(Pybind11Util INTERFACE pybind11::module)

# set_target_properties(Pybind11Util PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
#                                             SUFFIX "${PYTHON_MODULE_EXTENSION}")


# Test #
########

enable_testing()

add_subdirectory(test)


add_subdirectory(example/SimpleWrap)

# Install #
###########

# install(TARGETS Pybind11Util EXPORT Pybind11UtilTargets)

# install(DIRECTORY inc/ma DESTINATION include)

# install(EXPORT Pybind11UtilTargets DESTINATION lib/cmake/Pybind11Util)

# export(TARGETS Pybind11Util FILE Pybind11UtilTargets.cmake)

