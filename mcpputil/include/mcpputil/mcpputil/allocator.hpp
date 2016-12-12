#pragma once
#include <cassert>
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
  template <typename InputIt1, typename InputIt2, typename Allocator>
  void uninitialied_shift_by_n_pos(InputIt1 first, InputIt2 last, ptrdiff_t count, Allocator &allocator)
  {
    assert(count >= 0);
    for (auto it = last; it != first; --it) {
      ::std::allocator_traits<Allocator>::construct(allocator, it, ::std::move(*(it - count)));
      ::std::allocator_traits<Allocator>::destroy(allocator, (it - count));
    }
  }
  template <typename InputIt1, typename InputIt2, typename Allocator>
  void uninitialized_shift_by_n_neg(InputIt1 first, InputIt2 last, ptrdiff_t count, Allocator &allocator)
  {
    assert(count >= 0);
    for (auto it = first; it != last; ++it) {
      ::std::allocator_traits<Allocator>::construct(allocator, it, ::std::move(*(it + count)));
      ::std::allocator_traits<Allocator>::destroy(allocator, (it + count));
    }
  }

  template <class ForwardIt, class Size, typename Allocator>
  ForwardIt uninitialized_default_construct_n(ForwardIt first, Size n, Allocator &allocator)
  {
    ForwardIt current = first;
    try {
      for (; n > 0; (void)++current, --n) {
        ::std::allocator_traits<Allocator>::construct(allocator, ::std::addressof(*current));
      }
      return current;
    } catch (...) {
      for (; first != current; ++first) {
        ::std::allocator_traits<Allocator>::destroy(allocator, first);
      }
      throw;
    }
  }
  template <class ForwardIt, class Size, class T, typename Allocator>
  ForwardIt uninitialized_fill_n(ForwardIt first, Size count, const T &value, Allocator &allocator)
  {
    ForwardIt current = first;
    try {
      for (; count > 0; ++current, (void)--count) {
        ::std::allocator_traits<Allocator>::construct(allocator, ::std::addressof(*current), value);
      }
      return current;
    } catch (...) {
      for (; first != current; ++first) {
        ::std::allocator_traits<Allocator>::destroy(allocator, first);
      }
      throw;
    }
  }

  template <class InputIt, class Size, class ForwardIt, typename Allocator>
  ForwardIt uninitialized_copy_n(InputIt first, Size count, ForwardIt d_first, Allocator allocator)
  {
    ForwardIt current = d_first;
    try {
      for (; count > 0; ++first, (void)++current, --count) {
        ::std::allocator_traits<Allocator>::construct(allocator, ::std::addressof(*current), *first);
      }
    } catch (...) {
      for (; d_first != current; ++d_first) {
        ::std::allocator_traits<Allocator>::destroy(allocator, first);
      }
      throw;
    }
    return current;
  }
}
