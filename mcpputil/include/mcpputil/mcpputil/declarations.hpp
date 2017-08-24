#pragma once
#ifdef _WIN32
#ifndef MCPPUTIL_DISABLE_ITERATOR_DEBUG
//#undef _ITERATOR_DEBUG_LEVEL
//#define _ITERATOR_DEBUG_LEVEL 0
#endif
#endif
#include <cstddef>
#include <cstdint>
#ifndef _WIN32
// NOT WIN32
#ifndef MCPPALLOC_NO_INLINES
#define MCPPALLOC_SPARSE_INLINES
#define MCPPALLOC_INLINES
#define MCPPALLOC_OPT_INLINE inline
#define MCPPALLOC_ALWAYS_INLINE __attribute__((always_inline)) inline
#define MCPPALLOC_OPT_ALWAYS_INLINE __attribute__((always_inline)) inline
#else
#define MCPPALLOC_OPT_INLINE
#define MCPPALLOC_ALWAYS_INLINE inline
#define MCPPALLOC_OPT_ALWAYS_INLINE inline
#endif
#define MCPPALLOC_POSIX
#define MCPPALLOC_NO_INLINE __attribute__((noinline))
#define mcpputil_likely(x) __builtin_expect(static_cast<bool>(x), 1)
#define mcpputil_unlikely(x) __builtin_expect(static_cast<bool>(x), 0)
#define mcpputil_always_inline __attribute__((always_inline)) inline
#define if_constexpr if constexpr
#else
// WIN32
#define MCPPALLOC_OPT_INLINE
#define MCPPALLOC_ALWAYS_INLINE inline
#define MCPPALLOC_OPT_ALWAYS_INLINE inline
#define if_constexpr if
#define mcpputil_likely(x) x
#define mcpputil_unlikely(x) x
#define mcpputil_always_inline inline
// constant expr warning
#pragma warning(disable : 4127)
#pragma warning(disable : 4251)
// truncated name warning
#pragma warning(disable : 4503)
#pragma warning(disable : 4592)
#pragma warning(disable : 4100)
#pragma warning(disable : 5030)
#define MCPPALLOC_NO_INLINE __declspec(noinline)
#endif
#define BOOST_NO_AUTO_PTR

#pragma once
#if defined _WIN32 || defined __CYGWIN__
#ifdef mcpputil_EXPORTS
#ifdef __GNUC__
#define MCPPUTIL_DLL_PUBLIC __attribute__((dllexport))
#else
#define MCPPUTIL_DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define MCPPUTIL_DLL_PUBLIC __attribute__((dllimport))
#else
#define MCPPUTIL_DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define MCPPUTIL_DLL_LOCAL
#else
#define MCPPUTIL_DLL_PUBLIC __attribute__((visibility("default")))
#define MCPPUTIL_DLL_LOCAL __attribute__((visibility("hidden")))
#endif

#ifdef _WIN32
#define MCPPUTIL_PUBLIC __declspec(dllexport)
#else
#define MCPPUTIL_PUBLIC __attribute__((visibility("default")))
#endif

namespace mcpputil
{
  /**
   * \brief Return 2^n.
   **/
  inline constexpr size_t pow2(int n) noexcept
  {
    return static_cast<size_t>(2) << (n - 1);
  }
  /**
   * \brief Functor that does nothing.
   **/
  struct do_nothing_t {
    template <typename... Args>
    void operator()(Args &&...) const noexcept
    {
    }
  };
}
