#include <mcpputil/mcpputil/declarations.hpp>
// This Must be first.
#include <mcpputil/mcpputil/memory_range.hpp>
#include <ostream>

namespace mcpputil
{
  template <>
  ::std::ostream &operator<<(::std::ostream &stream, const memory_range_t<void *> &range)
  {
    stream << "(" << reinterpret_cast<void *>(range.begin()) << "," << reinterpret_cast<void *>(range.end()) << ")";
    return stream;
  }
} // namespace mcpputil
