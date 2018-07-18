project(wyrm_test)

find_package(GTest REQUIRED)

add_executable(wyrm_test
    src/numpyHandlerTest.cpp
)

target_compile_features(wyrm_test PUBLIC cxx_std_14)

target_link_libraries(wyrm_test
    PRIVATE GTest::GTest GTest::Main wyrm pybind11::embed)

# gtest_add_tests(TARGET wyrm_test
#     TEST_SUFFIX .noArgs
#     TEST_LIST   noArgsTests
# )
# set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)