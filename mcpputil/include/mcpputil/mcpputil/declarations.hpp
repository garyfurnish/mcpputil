#pragma once
#ifdef _WIN32
#undef _ITERATOR_DEBUG_LEVEL
#define _ITERATOR_DEBUG_LEVEL 0
#endif
#include <algorithm>
#include <assert.h>
#include <cstddef>
#include <memory>
#include <stdint.h>
#include <stdlib.h>
#include <tuple>
#ifndef _WIN32
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
#define MCPPALLOC_POSIX
#define mcpputil_builtin_prefetch(ADDR) __builtin_prefetch(ADDR)
#define mcpputil_builtin_clz1(X) __builtin_clzl(X)
#ifndef mcpputil_builtin_current_stack
#define mcpputil_builtin_current_stack(...) __builtin_frame_address(0)
#endif
#define MCPPALLOC_NO_INLINE __attribute__((noinline))
#define mcpputil_likely(x) __builtin_expect(static_cast<bool>(x), 1)
#define mcpputil_unlikely(x) __builtin_expect(static_cast<bool>(x), 0)
#define mcpputil_always_inline __attribute__((always_inline)) inline
#define if_constexpr                                                                                                             \
  if                                                                                                                             \
  constexpr
#else
#define MCPPALLOC_OPT_INLINE
#define MCPPALLOC_ALWAYS_INLINE
#define MCPPALLOC_OPT_ALWAYS_INLINE inline
#define mcpputil_builtin_prefetch(ADDR) _m_prefetch(ADDR)
#define mcpputil_builtin_clz1(X) (63 - __lzcnt64(X))
#define if_constexpr if
#ifndef mcpputil_builtin_current_stack
#define mcpputil_builtin_current_stack() _AddressOfReturnAddress()
#define mcpputil_likely(x) x
#define mcpputil_unlikely(x) x
#define mcpputil_always_inline inline
#endif
// spurious error generation in nov ctp.
// constant expr warning
#pragma warning(disable : 4127)
#pragma warning(disable : 4251)
#pragma warning(disable : 4592)
#pragma warning(disable : 4100)
#pragma warning(disable : 5030)
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
  /**
   * \brief Hide a pointer from garbage collection in a unspecified way.
   **/
  mcpputil_always_inline uintptr_t hide_pointer(void *v)
  {
    return ~reinterpret_cast<size_t>(v);
  }
  /**
   * \brief Unide a pointer from garbage collection in a unspecified way.
   **/
  mcpputil_always_inline void *unhide_pointer(uintptr_t sz)
  {
    return reinterpret_cast<void *>(~sz);
  }

  /**
   * \brief Return 2^n.
   **/
  inline constexpr size_t pow2(int n)
  {
    return static_cast<size_t>(2) << (n - 1);
  }

  /**
   * \brief Return inverse for size.
   **/
  mcpputil_always_inline constexpr size_t size_inverse(size_t t)
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
