cmake_minimum_required(VERSION 3.6)

# Global option #
#################

# SimpleWrap #
##############

project(SimpleWrap LANGUAGES CXX)

add_library(SimpleWrap MODULE
    src/function.cpp
    src/wrap.cpp)

target_compile_features(SimpleWrap PRIVATE cxx_std_14)

target_include_directories(SimpleWrap PRIVATE inc)

target_link_libraries(SimpleWrap PRIVATE wyrm)

set_target_properties(SimpleWrap PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                            SUFFIX "${PYTHON_MODULE_EXTENSION}")