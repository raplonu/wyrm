#include <wyrm>

namespace py = pybind11;

class Toto
{
  Toto() = default;
  Toto(const Toto &) = default;
  public:
  static Toto & fun(){static Toto t; return t;}
};

#include <function.h>

PYBIND11_MODULE(SimpleWrap, m) {
  m.doc() = "Simplewrap library module";

  m.def("add", &me_add, "add two number");
  m.def("sum", wy::rowCast(me_sum), "sum size elements of ptr");

  py::class_<Toto>(m, "Toto")
    .def_static("fun", wy::rowCast(Toto::fun));

}
