set (CMAKE_CXX_STANDARD 14)

project(wyrm_test)

find_package(GTest REQUIRED)

add_executable(wyrm_test
    src/numpyHandlerTest.cpp
)

# pybind11_add_module(wyrm_test src/numpyHandlerTest.cpp)

target_link_libraries(wyrm_test
    PRIVATE GTest::GTest GTest::Main wyrm)

# gtest_add_tests(TARGET wyrm_test
#     TEST_SUFFIX .noArgs
#     TEST_LIST   noArgsTests
# )
# set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)