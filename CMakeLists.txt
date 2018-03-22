cmake_minimum_required(VERSION 3.6)

# Global option #
#################

set (CMAKE_CXX_STANDARD 14)

# Wyrm #
##############

project(wyrm VERSION 0.1 LANGUAGES CXX)

add_library(wyrm INTERFACE)

target_include_directories(wyrm INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>  
    $<INSTALL_INTERFACE:inc>
)

# Add pybind
add_subdirectory(pybind)

target_link_libraries(wyrm INTERFACE pybind11::module)

# Test #
########

enable_testing()

add_subdirectory(test)

add_subdirectory(example/SimpleWrap)

# Install #
###########

# install(TARGETS wyrm EXPORT wyrm_targets)

# install(DIRECTORY inc/ma DESTINATION include)

# install(EXPORT wyrm_targets DESTINATION lib/cmake/wyrm)

# export(TARGETS wyrm FILE wyrm_targets.cmake)

