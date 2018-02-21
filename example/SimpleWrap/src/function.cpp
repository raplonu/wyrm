#include <function.h>

int me_add(int i, int j)
{
    return i + j;
}

int me_sum(int * ptr, int size)
{
    int res(0);

    for(int i(0); i < size; ++i)
        res += ptr[i];

    return res;
}