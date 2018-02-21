#include <gtest/gtest.h>

#include <ma/ma>
#include <PybindUtil>

using namespace pu;

namespace
{
    void fun1(){}

    TEST(Numpy_handler, simple_interface)
    {
        auto f = castParameter(fun1);

        f();
    }

    int fun2(int i){ return i + 1;}

    TEST(Numpy_handler, simple_return)
    {
        auto add_1 = castParameter(fun2);

        EXPECT_EQ(add_1(1), 2);
    }


}