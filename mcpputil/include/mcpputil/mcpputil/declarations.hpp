#pragma once
#ifdef _WIN32
#define _ITERATOR_DEBUG_LEVEL 0
#endif
#include <algorithm>
#include <assert.h>
#include <cstddef>
#include <memory>
#include <stdint.h>
#include <stdlib.h>
#include <tuple>
#ifndef MCPPALLOC_NO_INLINES
#define MCPPALLOC_SPARSE_INLINES
#define MCPPALLOC_INLINES
#define MCPPALLOC_OPT_INLINE inline
#define MCPPALLOC_ALWAYS_INLINE __attribute__((always_inline)) inline
#define MCPPALLOC_OPT_ALWAYS_INLINE __attribute__((always_inline)) inline
#else
#define MCPPALLOC_OPT_INLINE
#define MCPPALLOC_ALWAYS_INLINE
#define MCPPALLOC_OPT_ALWAYS_INLINE inline
#endif
#ifndef _WIN32
#define MCPPALLOC_POSIX
#define mcpputil_builtin_prefetch(ADDR) __builtin_prefetch(ADDR)
#define mcpputil_builtin_clz1(X) __builtin_clzl(X)
#ifndef mcpputil_builtin_current_stack
#define mcpputil_builtin_current_stack(...) __builtin_frame_address(0)
#endif
#define MCPPALLOC_NO_INLINE __attribute__((noinline))
#define mcpputil_likely(x) __builtin_expect(static_cast<bool>(x), 1)
#define mcpputil_unlikely(x) __builtin_expect(static_cast<bool>(x), 0)
#else
#define mcpputil_builtin_prefetch(ADDR) _m_prefetch(ADDR)
#define mcpputil_builtin_clz1(X) (63 - __lzcnt64(X))
#ifndef mcpputil_builtin_current_stack
#define mcpputil_builtin_current_stack() _AddressOfReturnAddress()
#endif
// spurious error generation in nov ctp.
#pragma warning(disable : 4592)
#pragma warning(disable : 4100)
#define MCPPALLOC_NO_INLINE __declspec(noinline)
#endif
namespace mcpputil
{
  /**
   * \brief Alignment on this system in bytes.
  **/
  static constexpr size_t c_alignment = 16;
  /**
   * \brief Power of two to align to on this system.
  **/
  static constexpr size_t c_align_pow2 = 4;
  static_assert((1 << c_align_pow2) == c_alignment, "Alignment not valid.");
  /**
   * \brief Align size to system alignment.
   **/
  inline constexpr size_t align(size_t size)
  {
    return ((size + c_alignment - 1) >> c_align_pow2) << c_align_pow2;
  }

#if defined(_DEBUG) || not defined(NDEBUG)
#ifndef MCPPALLOC_DEBUG_LEVEL
#define MCPPALLOC_DEBUG_LEVEL 0
#endif
#endif
#ifndef MCPPALLOC_DEBUG_LEVEL
#define MCPPALLOC_DEBUG_LEVEL 0
#endif
  /**
   * \brief Current debug level.
   **/
  static const constexpr int c_debug_level = MCPPALLOC_DEBUG_LEVEL;
  /**
   * \brief Hide a pointer from garbage collection in a unspecified way.
   **/
  __attribute__((always_inline)) inline uintptr_t hide_pointer(void *v)
  {
    return ~reinterpret_cast<size_t>(v);
  }
  /**
   * \brief Unide a pointer from garbage collection in a unspecified way.
   **/
  __attribute__((always_inline)) inline void *unhide_pointer(uintptr_t sz)
  {
    return reinterpret_cast<void *>(~sz);
  }

  namespace details
  {
    /**
     * \brief Return 2^n.
    **/
    inline constexpr size_t pow2(int n)
    {
      return static_cast<size_t>(2) << (n - 1);
    }
  }
  using details::pow2;

  /**
   * \brief Return inverse for size.
   **/
  __attribute__((always_inline)) inline constexpr size_t size_inverse(size_t t)
  {
    return ~t;
  }
  /**
   * \brief Functor that does nothing.
   **/
  struct do_nothing_t {
    template <typename... Args>
    void operator()(Args &&...)
    {
    }
  };
}
