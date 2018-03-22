#include <wyrm>

namespace py = pybind11;

#include <function.h>

PYBIND11_MODULE(SimpleWrap, m) {
    m.doc() = "Simplewrap library module";

    m.def("add", &me_add, "add two number");
    m.def("sum", wy::castParameter(me_sum), "sum size elements of ptr");

}
