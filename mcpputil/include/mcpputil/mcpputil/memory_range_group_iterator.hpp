#pragma once
#include "memory_range_group.hpp"
namespace mcpputil
{
  template <typename Memory_Range_Group, bool is_const>
  class memory_range_group_iterator_t
  {
  public:
    static constexpr const bool cs_is_const = is_const;

  protected:
  }
}
