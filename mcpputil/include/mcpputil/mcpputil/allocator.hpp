#pragma once
#include <cstddef>
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
  template <typename InputIt, typename Allocator>
  void uninitialied_shift_by_n_pos(InputIt first, InputIt last, ptrdiff_t count, Allocator &allocator)
  {
    assert(count >= 0);
    for (auto it = last; it != first; --it) {
      ::std::allocator_traits<Allocator>::construct(allocator, it + count, ::std::move(*it));
      ::std::allocator_traits<Allocator>::destroy(allocator, it);
    }
  }
  template <typename InputIt, typename Allocator>
  void uninitialized_shift_by_n_neg(InputIt first, InputIt last, ptrdiff_t count, Allocator &allocator)
  {
    assert(count >= 0);
    for (auto it = first; it != last; ++it) {
      ::std::allocator_traits<Allocator>::construct(allocator, it - count, ::std::move(*it));
      ::std::allocator_traits<Allocator>::destroy(allocator, it);
    }
  }
}
