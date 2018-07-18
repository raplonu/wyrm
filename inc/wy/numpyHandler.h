#ifndef WY_NUMPY_HANDLER_H
#define WY_NUMPY_HANDLER_H

#include <pybind11/numpy.h>

namespace wy {

using pybind11::detail::is_pod_struct;

template<typename T>
using enableAdapt = typename std::enable_if<(std::is_scalar<T>::value or is_pod_struct<T>::value) and  not std::is_const<T>::value>::type;

template <typename T, typename = void>
struct RowMajorAdapter
{
  using type = T;

  static T cast(type t) { return t; }
};

template <typename T>
struct RowMajorAdapter<const T *, enableAdapt<T>> {
  using type = const pybind11::array_t<T> &;

  static const T *cast(type t) { return t.data(); }
};

template <typename T>
struct RowMajorAdapter<T *, enableAdapt<T>> {
  using type = pybind11::array_t<T> &;

  static T *cast(type t) { return t.mutable_data(); }
};

template<>
struct RowMajorAdapter<const char *>
{
  using type = const char *;

  static type cast(type t) { return t; }
};

template<>
struct RowMajorAdapter<char *>
{
  using type = char *;

  static type cast(type t) { return t; }
};

template<typename T>
using array_f = pybind11::array_t<T, pybind11::array::f_style | pybind11::array::forcecast>;

template <typename T, typename = void>
struct ColMajorAdapter
{
  using type = T;

  static T cast(type t) { return t; }
};

template <typename T>
struct ColMajorAdapter<const T *, enableAdapt<T>> {
  using type = const array_f<T> &;

  static const T *cast(type t) { return t.data(); }
};

template <typename T>
struct ColMajorAdapter<T *, enableAdapt<T>> {
  using type = array_f<T> &;

  static T *cast(type t) { return t.mutable_data(); }
};

template<>
struct ColMajorAdapter<const char *>
{
  using type = const char *;

  static type cast(type t) { return t; }
};

template<>
struct ColMajorAdapter<char *>
{
  using type = char *;

  static type cast(type t) { return t; }
};

}  // namespace wy

#endif  // WY_NUMPY_HANDLER_H
