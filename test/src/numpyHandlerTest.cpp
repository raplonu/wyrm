#include <gtest/gtest.h>

#include <wyrm>

using namespace wy;

namespace
{
    int fun1(){return 3;}

    TEST(Numpy_handler, simple_interface)
    {
        auto f = castParameter(fun1);

        EXPECT_EQ(f(), 3);
    }

    int fun2(int i){ return i + 1;}

    TEST(Numpy_handler, simple_return)
    {
        auto f2 = castParameter(fun2);

        EXPECT_EQ(f2(1), 2);
    }

    const int * fun3(const int * ptr){return ptr;}

    TEST(Numpy_handler, numpy_data_return)
    {
        auto f3 = castParameter(fun3);

        pybind11::array_t<int> data;

        EXPECT_EQ(f3(data), data.data());
    }

}