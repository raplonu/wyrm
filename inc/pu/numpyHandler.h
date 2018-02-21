#pragma once
#ifndef NUMPY_HANDLER_H
#define NUMPY_HANDLER_H

//#include <pybind11/numpy.h>
#include "autoCastParameter.h"

namespace py
{
    template<typename T>
    struct array_t
    {
        T * t;
        array_t(T * t):t(t){}

        T * mutable_data()
        {
            return t;
        }

        T const * data() const
        {
            return t;
        }
    };
}

template<typename T>
struct Adapt<T const *>
{
    using type = py::array_t<T> const;

    static T const * cast(type t)
    {
        return t.data();
    }
};

template<typename T>
struct Adapt<T*>
{
    using type = py::array_t<T>;

    static T * cast(type t)
    {
        return t.mutable_data();
    }
};

#endif //NUMPY_HANDLER_H

