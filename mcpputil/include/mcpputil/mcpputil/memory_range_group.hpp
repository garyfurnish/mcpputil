#pragma once
#include "memory_range.hpp"
#include <mcpputil/mcpputil/boost/container/flat_set.hpp>
namespace mcpputil
{
  template <typename Memory_Range, typename Allocator>
  class memory_range_group_t
  {
  public:
    using memory_range_type = Memory_Range;

    auto include_begin() noexcept;
    auto include_begin() const noexcept;
    auto include_cbegin() const noexcept;
    auto include_end();
    auto include_end() const noexcept;
    auto include_cend() const noexcept;

    auto contains() const noexcept -> bool;

  protected:
    using memory_range_allocator_type = typename Allocator::template rebind<memory_range_type>::other;
    ::boost::container::flat_set<memory_range_type, ::std::less<>, memory_range_allocator_type> m_include;
    ::boost::container::flat_set<memory_range_type, ::std::less<>, memory_range_allocator_type> m_exclude;
  };
} // namespace mcpputil
