#ifndef WYRM_AUTO_CAST_PARAMETER_H
#define WYRM_AUTO_CAST_PARAMETER_H

#include <functional>
#include <type_traits>
#include <utility>

namespace wy {

template <typename...>
struct types {
  using type = types;
};

template <typename Fn>
struct args;

template <typename R, typename... Args>
struct args<R(Args...)> : types<Args...> {};

template <typename R, typename... Args>
struct args<R (&)(Args...)> : types<Args...> {};

template <typename R, typename T, typename... Args>
struct args<R (T::*)(Args...)> : types<T&, Args...> {};

template <typename R, typename T, typename... Args>
struct args<R (T::*)(Args...) const> : types<T&, Args...> {};

template <typename R, typename... Args>
struct args<std::function<R(Args...)>> : types<Args...> {};

template <typename Fn>
using args_t = typename args<Fn>::type;

template <typename T, typename = void>
struct DefaultAdapter {
  using type = T;

  template <typename TT>
  static TT cast(TT&& t) {
    return std::forward<TT>(t);
  }
};

#if (__cplusplus >= 201703L)

template <template<typename...> class Adaptator = DefaultAdapter, typename Fn, typename... FnArgs>
auto castParameter_impl(Fn&& fn, types<FnArgs...>) {
  return [&fn](typename Adaptator<FnArgs>::type... args) -> decltype(auto) {
    // Use invoke to manage method function call
    return std::invoke(fn, Adaptator<FnArgs>::cast(std::forward<typename Adaptator<FnArgs>::type>(args))...);
  };
}

namespace impl {
  template <typename Fn>
  auto makefFn(Fn&& fn) {
    // Use class template argument deduction to deduce function signature in case
    // of lambda
    return std::function{std::forward<Fn>(fn)};
  }
}  // namespace impl

template <typename Fn>
using fn_type = decltype(impl::makefFn(std::declval<Fn&>()));

template <template<typename...> class Adaptator = DefaultAdapter, typename Fn>
auto castParameter(Fn&& fn) {
  // Test if fn is a member function because cant be used with std::function in
  // fn_type
  if constexpr (std::is_member_function_pointer_v<Fn>)
    return castParameter_impl<Adaptator>(std::forward<Fn>(fn), args_t<Fn>{});
  else
    return castParameter_impl<Adaptator>(std::forward<Fn>(fn), args_t<fn_type<Fn>>{});
}

#else  //(__cplusplus < 201703L)

template <
    template<typename...> class Adaptator,
    typename Fn, typename Obj, typename... FnArgs,
    typename = std::enable_if_t<std::is_member_function_pointer<Fn>::value>>
auto castParameter_impl(Fn&& fn, types<Obj, FnArgs...>) {
  return [fn](Obj obj, typename Adaptator<FnArgs>::type... args) -> decltype(auto) {
    return (obj.*fn)(Adaptator<FnArgs>::cast(std::forward<typename Adaptator<FnArgs>::type>(args))...);
  };
}


template <
    template<typename...> class Adaptator,
    typename Fn, typename... FnArgs,
    typename = std::enable_if_t<not std::is_member_function_pointer<Fn>::value>>
auto castParameter_impl(Fn&& fn, types<FnArgs...>) {
  return [&fn](typename Adaptator<FnArgs>::type... args) -> decltype(auto) {
    return fn(Adaptator<FnArgs>::cast(std::forward<typename Adaptator<FnArgs>::type>(args))...);
  };
}

template <template<typename...> class Adaptator = DefaultAdapter, typename Fn>
auto castParameter(Fn&& fn) {
  return castParameter_impl<Adaptator>(std::forward<Fn>(fn), args_t<Fn>{});
}

#endif  //(__cplusplus >= 201703L)
}  // namespace wy

#endif  // WYRM_AUTO_CAST_PARAMETER_H
