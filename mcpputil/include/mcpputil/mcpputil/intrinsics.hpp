#pragma once
#include "declarations.hpp"
#ifndef _WIN32
// NOT WIN32
#include <emmintrin.h>
#if defined(__AVX__) && !defined(__APPLE__)
#include <immintrin.h>
#endif
#define mcpputil_builtin_prefetch(ADDR) __builtin_prefetch(ADDR)
#define mcpputil_builtin_clz1(X) __builtin_clzl(X)
#define mcpputil_builtin_current_stack() __builtin_frame_address(0)
namespace mcpputil
{
  mcpputil_always_inline size_t popcount(size_t x)
  {
    return static_cast<size_t>(__builtin_popcountll(x));
  }
  mcpputil_always_inline size_t ffs(uint64_t x)
  {
    return static_cast<size_t>(__builtin_ffsll(static_cast<long long>(x)));
  }
  mcpputil_always_inline size_t clz(size_t x)
  {
    return static_cast<size_t>(__builtin_clzll(x));
  }
#else
// WIN32
#define mcpputil_builtin_prefetch(ADDR) _m_prefetch(ADDR)
#define mcpputil_builtin_clz1(X) (63 - __lzcnt64(X))
#define mcpputil_builtin_current_stack() _AddressOfReturnAddress()

#include <intrin.h>
namespace mcpputil
{
  mcpputil_always_inline size_t popcount(size_t x)
  {
    return __popcnt64(x);
  }
  mcpputil_always_inline size_t ffs(uint64_t x)
  {
    unsigned long index{0};
    if (!_BitScanForward64(&index, x))
      return 0;
    index++;
    return index;
  }
  mcpputil_always_inline size_t clz(size_t x)
  {
    unsigned long index{0};
    char found = _BitScanReverse64(&index, x);
    if (!found)
      return 64;
    return (63 - index);
  }
#endif
}
