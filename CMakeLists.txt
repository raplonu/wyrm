cmake_minimum_required(VERSION 3.1)

# Global option #
#################

# PybindUtil 0 #
#######################

project(PybindUtil VERSION 0.1 LANGUAGES CXX)

target_include_directories(PybindUtil INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>  
    $<INSTALL_INTERFACE:inc>
)

# Add pybind
add_subdirectory(pybind11)

target_link_libraries(PybindUtil PUBLIC pybind11::module)

set_target_properties(PybindUtil PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                            SUFFIX "${PYTHON_MODULE_EXTENSION}")


# Install #
###########

install(TARGETS PybindUtil EXPORT PybindUtilTargets)

install(DIRECTORY inc/ma DESTINATION include)

install(EXPORT PybindUtilTargets DESTINATION lib/cmake/PybindUtil)

export(TARGETS PybindUtil FILE PybindUtilTargets.cmake)

