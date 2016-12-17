#include "declarations.hpp"
#include <gsl/gsl>
#include <stdexcept>

#pragma once
namespace mcpputil
{
  /**
   * \brief Default alignment on this system for mcpputils in bytes.
  **/
  static constexpr size_t c_alignment = 16;
  /**
   * \brief Default alignment on this system.
   **/
  static constexpr size_t cs_default_alignment = 8;
  /**
   * \brief Default cache line size on reasonable systems
   **/
  static constexpr size_t cs_default_cache_line_size = 64;
  /**
   * \brief Power of two to align to on this system.
  **/
  static constexpr size_t c_align_pow2 = 4;
  static_assert((1 << c_align_pow2) == c_alignment, "Alignment not valid.");
  /**
   * \brief Align size to system alignment.
   **/
  inline constexpr size_t align(size_t size) noexcept
  {
    return ((size + c_alignment - 1) >> c_align_pow2) << c_align_pow2;
  }

  /**
   * \brief Align size to alignment.
   **/
  inline constexpr ptrdiff_t align(ptrdiff_t sz, ptrdiff_t alignment) noexcept
  {
    if (sz <= 0) {
      throw ::std::runtime_error("Align error");
    }
    if (alignment <= 0) {
      throw ::std::runtime_error("Align error");
    }
    auto ret = ((sz + alignment - 1) / alignment) * alignment;
    if (mcpputil_unlikely(ret < 0)) {
      throw ::std::runtime_error("Align error");
    }
    return ret;
  }
  /**
   * \brief Align pointer to alignment.
  **/
  inline void *align(void *iptr, size_t alignment) noexcept
  {
    return reinterpret_cast<void *>(align(reinterpret_cast<ptrdiff_t>(iptr), gsl::narrow_cast<ptrdiff_t>(alignment)));
  }
  /**
   * \brief Align pointer to alignment.
  **/
  inline const void *align(const void *iptr, size_t alignment) noexcept
  {
    return reinterpret_cast<void *>(align(reinterpret_cast<ptrdiff_t>(iptr), gsl::narrow_cast<ptrdiff_t>(alignment)));
  }

  /**
   * \brief Align size to a given power of 2.
  **/
  inline constexpr size_t align_pow2(size_t size, size_t align_pow) noexcept
  {
    return ((size + (static_cast<size_t>(1) << align_pow) - 1) >> align_pow) << align_pow;
  }
  /**
   * \brief Align pointer to a given power of 2.
  **/
  template <typename T>
  inline constexpr T *align_pow2(T *iptr, size_t align_pow) noexcept
  {
    return reinterpret_cast<T *>(align_pow2(reinterpret_cast<size_t>(iptr), align_pow));
  }
}
