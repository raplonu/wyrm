#include <gtest/gtest.h>

#include <pybind11/embed.h>
#include <wyrm>

// Preparation for test Numpy_handler::CustomTypeConvertion
struct CustomType{int val;};

namespace wy
{
  template<>
  struct RowMajorAdapter<CustomType *>
  {
    using type = CustomType *;
    static CustomType * cast(CustomType * t) {t->val++; return t; }
  };
}

struct NonPod
{
  NonPod(int val):val(val){}

  virtual int get(){ return val; }
  int val;
};

using namespace wy;

namespace {
  int fun1() { return 3; }

  TEST(Numpy_handler, simple_interface) {
    auto f = rowCast(fun1);

    EXPECT_EQ(f(), 3);
  }

  int fun2(int i) { return i + 1; }

  TEST(Numpy_handler, simple_return) {
    auto f2 = rowCast(fun2);

    EXPECT_EQ(f2(1), 2);
  }

  const int* fun3(const int* ptr) { return ptr; }

  TEST(Numpy_handler, row_major_data_return) {
    auto f3 = rowCast(fun3);

    pybind11::initialize_interpreter();

    std::vector<int> v(10);
    pybind11::array_t<int> data(10, v.data());

    EXPECT_EQ(f3(data), data.data());

    pybind11::finalize_interpreter();
  }

  TEST(Numpy_handler, column_major_data_return) {
    auto f3 = colCast(fun3);

    pybind11::initialize_interpreter();

    std::vector<int> v(10);
    wy::array_f<int> data(10, v.data());

    EXPECT_EQ(f3(data), data.data());

    pybind11::finalize_interpreter();
  }

  const char* fun4(const char* string){return string;}

  TEST(Numpy_handler, charNonConvertion) {
    auto f4 = rowCast(fun4);

    const char * text = "this is text";

    EXPECT_STREQ(f4(text), text);
  }



  CustomType fun5(CustomType * ct){return *ct;}

  TEST(Numpy_handler, CustomTypeConvertion) {
    auto f5 = rowCast(fun5);

    CustomType ct{42};

    EXPECT_EQ(f5(&ct).val, 43);
    EXPECT_EQ(ct.val, 43);
  }

  NonPod& fun6(NonPod * np){return *np;}

  TEST(Numpy_handler, NonPodStructHandle) {
    auto f6 = rowCast(fun6);

    NonPod np(42);
    
    EXPECT_EQ(f6(&np).get(), 42);
  }

}  // namespace
