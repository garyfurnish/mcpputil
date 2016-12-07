#pragma once
#include "declarations.hpp"
namespace mcpputil
{
  /**
   * \brief Return inverse for size.
   **/
  mcpputil_always_inline constexpr size_t bitwise_negate(size_t t) noexcept
  {
    return ~t;
  }
}
