#pragma once
#include <cstddef>
#include <cstdint>
namespace mcpputil
{
  /**
   * \brief Adjust pointer by byte offset.
   *
   * Default rounding behavior if offset not integer multiple
   **/
  template <typename Ptr_Underlying>
  void adjust_pointer_by_offset(Ptr_Underlying *&ptr, ptrdiff_t offset)
  {
    ptr = reinterpret_cast<Ptr_Underlying *>(reinterpret_cast<uint8_t *>(ptr) + offset);
  }
} // namespace mcpputil
