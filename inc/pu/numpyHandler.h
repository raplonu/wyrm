#pragma once
#ifndef NUMPY_HANDLER_H
#define NUMPY_HANDLER_H

#include <pybind11/numpy.h>
#include <pu/autoCastParameter.h>

namespace pu
{
    template<typename T>
    struct Adapt<T const *>
    {
        using type = pybind11::array_t<T> const;

        static T const * cast(type t)
        {
            return t.data();
        }
    };

    template<typename T>
    struct Adapt<T*>
    {
        using type = pybind11::array_t<T>;

        static T * cast(type t)
        {
            return t.mutable_data();
        }
    };

}

#endif //NUMPY_HANDLER_H

