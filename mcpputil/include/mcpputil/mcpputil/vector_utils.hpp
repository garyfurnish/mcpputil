#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
namespace mcpputil
{
  /**
   * \brief Call reserve on vector.
   *
   * @param sz Size to reserve.
   * @return Offset in bytes from original location of vector data.
   **/
  template <typename T, typename Allocator>
  ptrdiff_t grow_by_reserve(::std::vector<T, Allocator> &vec, size_t sz)
  {
    if (vec.capacity() == 0) {
      vec.reserve(sz);
      return 0;
    }
    auto bbegin = &vec.front();
    vec.reserve(sz);
    auto offset = reinterpret_cast<uint8_t *>(&vec.front()) - reinterpret_cast<uint8_t *>(bbegin);
    return offset;
  }
}
