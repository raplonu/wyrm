cmake_minimum_required(VERSION 3.6)

# Global option #
#################

set (CMAKE_CXX_STANDARD 14)

# SimpleWrap #
##############

project(SimpleWrap LANGUAGES CXX)

add_library(SimpleWrap MODULE
    src/function.cpp
    src/wrap.cpp)

target_include_directories(SimpleWrap PRIVATE inc)

target_link_libraries(SimpleWrap PRIVATE wyrm)

set_target_properties(SimpleWrap PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                            SUFFIX "${PYTHON_MODULE_EXTENSION}")