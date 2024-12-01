#pragma once
#include <cstdint>

#define TO_STR_HELPER(X) #X
#define TO_STR(X) TO_STR_HELPER(X)

template<typename T>
void
copy(T from, size_t size, T to)
{
  for(size_t i = 0; i < size; i++)
    to[i] = from[i];
}

