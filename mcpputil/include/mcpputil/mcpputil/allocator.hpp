#pragma once
#include <memory>
namespace mcpputil
{
  template <typename InputIt, typename ForwardIt>
  void move_uninitialized(InputIt first, InputIt last, ForwardIt out)
  {
    std::uninitialized_copy(std::make_move_iterator(first), std::make_move_iterator(last), out);
  }
  template <typename InputIt, typename Allocator>
  void destroy(InputIt first, InputIt last, Allocator &allocator)
  {
    for (InputIt it = first; it != last; ++it) {
      ::std::allocator_traits<Allocator>::destroy(allocator, it);
    }
  }
}
