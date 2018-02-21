#pragma once
#ifndef AUTO_CAST_PARAMETER_H
#define AUTO_CAST_PARAMETER_H

#include <utility>
#include <functional>
#include <type_traits>

namespace pu
{
    template<typename...>struct types{using type=types;};

    template<typename Fn> struct args;

    template<typename R, typename...Args>
    struct args<R(Args...)>:types<Args...>{};

    template<typename R, typename...Args>
    struct args<R(&)(Args...)>:types<Args...>{};

    template<typename R, typename T, typename...Args>
    struct args<R(T::*)(Args...)>:types<T&, Args...>{};

    template<typename R, typename...Args>
    struct args<std::function<R (Args...)>>:types<Args...>{};

    template<typename Fn>
    using args_t = typename args<Fn>::type;

    template<typename T>
    struct Adapt
    {
        using type = T;

        template<typename TT>
        static TT cast(TT && t)
        {
            return std::forward<TT>(t);
        }
    };

    template<typename T>
    using Adapt_t = typename Adapt<T>::type;


    #if (__cplusplus >= 201703L) 

    template <typename...Args, typename Fn>
    auto castParameter_impl(types<Args...>, Fn && fn) {
        return [&fn](Adapt_t<Args>... args)
        {
            //Use invoke to manage method function call
            return std::invoke(std::forward<Fn>(fn), Adapt<Args>::cast(std::forward<Adapt_t<Args>>(args))...);
        };
    }

    namespace impl
    {
        template<typename Fn>
        auto makefFn(Fn && fn)
        {
            //Use class template argument deduction to deduce function signature in case of lambda
            return std::function{std::forward<Fn>(fn)};
        }
    }

    template<typename Fn>
    using fn_type = decltype(impl::makefFn(std::declval<Fn&>()));

    template<typename Fn>
    auto castParameter(Fn && fn)
    {
        //Test if fn is a member function because cant be used with std::function in fn_type
        if constexpr (std::is_member_function_pointer_v<Fn>)
            return castParameter_impl(args_t<Fn>{}, std::forward<Fn>(fn));
        else
        return castParameter_impl(args_t<fn_type<Fn>>{}, std::forward<Fn>(fn));
    }

    #else //(__cplusplus < 201703L)

    template <typename Param, typename...Args, typename Fn, typename = std::enable_if_t<is_member_function_pointer<Fn>::value>>
    auto castParameter_impl(types<Param, Args...>, Fn && fn) {
        return [&fn](Param param, typename Adapt<Args>::type... args)
        {
            return (param.*fn)(Adapt<Args>::cast(args)...);
        };
    }

    template <typename...Args, typename Fn, typename = std::enable_if_t<!is_member_function_pointer<Fn>::value>>
    auto castParameter_impl(types<Args...>, Fn && fn) {
        return [&fn](typename Adapt<Args>::type... args)
        {
            return fn(Adapt<Args>::cast(args)...);
        };
    }

    template<typename Fn>
    auto castParameter(Fn && fn)
    {
        return castParameter_impl(args_t<Fn>{}, std::forward<Fn>(fn));
    }

    #endif //(__cplusplus >= 201703L)
}

#endif //AUTO_CAST_PARAMETER_H