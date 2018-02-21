project(PybindUtilTest)

set (CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

set(PU_TEST_SRC
    src/numpyHandlerTest.cpp
)

add_executable(PybindUtilTest
    ${PU_TEST_SRC}
)

target_link_libraries(PybindUtilTest
    PRIVATE GTest::GTest GTest::Main Pybind11Util)


gtest_add_tests(TARGET PybindUtilTest
TEST_SUFFIX .noArgs
TEST_LIST   noArgsTests
)
set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)