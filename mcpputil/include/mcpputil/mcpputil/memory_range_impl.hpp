#pragma once
#include "unsafe_cast.hpp"
namespace mcpputil
{
  template <typename Pointer_Type>
  constexpr void
  memory_range_t<Pointer_Type>::set_begin(pointer_type begin) noexcept(::std::is_nothrow_move_assignable<pointer_type>::value)
  {
    ::std::get<0>(*this) = ::std::move(begin);
  }
  template <typename Pointer_Type>
  constexpr void
  memory_range_t<Pointer_Type>::set_end(pointer_type end) noexcept(::std::is_nothrow_move_assignable<pointer_type>::value)
  {
    ::std::get<1>(*this) = ::std::move(end);
  }
  template <typename Pointer_Type>
  constexpr void
  memory_range_t<Pointer_Type>::set(pointer_type begin,
                                    pointer_type end) noexcept(::std::is_nothrow_move_assignable<pointer_type>::value)
  {
    ::std::get<0>(*this) = ::std::move(begin);
    ::std::get<1>(*this) = ::std::move(end);
  }
  template <typename Pointer_Type>
  constexpr void memory_range_t<Pointer_Type>::set(::std::pair<pointer_type, pointer_type> pair) noexcept(
      ::std::is_nothrow_move_assignable<pointer_type>::value)
  {
    ::std::get<0>(*this) = ::std::move(pair.first);
    ::std::get<1>(*this) = ::std::move(pair.second);
  }
  template <typename Pointer_Type>
  constexpr auto memory_range_t<Pointer_Type>::begin() const noexcept(::std::is_nothrow_copy_constructible<pointer_type>::value)
      -> pointer_type
  {
    return ::std::get<0>(*this);
  }
  template <typename Pointer_Type>
  constexpr auto memory_range_t<Pointer_Type>::end() const noexcept(::std::is_nothrow_copy_constructible<pointer_type>::value)
      -> pointer_type
  {
    return ::std::get<1>(*this);
  }
  template <typename Pointer_Type>
  constexpr auto memory_range_t<Pointer_Type>::size() const noexcept -> size_type
  {
    return static_cast<size_type>(end() - begin());
  }
  template <typename Pointer_Type>
  constexpr auto memory_range_t<Pointer_Type>::empty() const noexcept -> bool
  {
    return size() == 0;
  }
  template <typename Pointer_Type>
  constexpr auto memory_range_t<Pointer_Type>::contains(const pointer_type &ptr) const noexcept -> bool
  {
    return ptr >= begin() && ptr < end();
  }
  template <typename Pointer_Type>
  template <typename New_Pointer_Type>
  constexpr auto memory_range_t<Pointer_Type>::cast() const noexcept -> memory_range_t<New_Pointer_Type>
  {
    return memory_range_t<New_Pointer_Type>(unsafe_cast<New_Pointer_Type>(begin()), unsafe_cast<New_Pointer_Type>(end()));
  }

  template <typename Pointer_Type>
  constexpr auto memory_range_t<Pointer_Type>::contains(const memory_range_t<pointer_type> &range) const noexcept -> bool
  {
    return begin() <= range.begin() && range.end() <= end();
  }
  template <typename Pointer_Type>
  template <typename T>
  constexpr auto memory_range_t<Pointer_Type>::contains(T &&t) const noexcept -> bool
  {
    return contains(static_cast<const pointer_type &>(reinterpret_cast<pointer_type>(t)));
  }

  template <typename Pointer_Type>
  constexpr auto memory_range_t<Pointer_Type>::size_comparator() noexcept
  {
    return [](const memory_range_t<pointer_type> &a, const memory_range_t<pointer_type> &b) noexcept->bool
    {
      return a.size() < b.size();
    };
  }
  template <typename Pointer_Type>
  constexpr auto operator==(const memory_range_t<Pointer_Type> &lhs, const memory_range_t<Pointer_Type> &rhs) noexcept -> bool
  {
    return lhs.begin() == rhs.begin() && lhs.end() == rhs.end();
  }
  template <typename Pointer_Type>
  constexpr auto operator!=(const memory_range_t<Pointer_Type> &lhs, const memory_range_t<Pointer_Type> &rhs) noexcept -> bool
  {
    return lhs.begin() != rhs.begin() || lhs.end != rhs.end();
  }
  template <typename Pointer_Type>
  constexpr auto operator<(const memory_range_t<Pointer_Type> &lhs, const memory_range_t<Pointer_Type> &rhs) noexcept -> bool
  {
    return lhs.begin() < rhs.begin();
  }
  template <typename Pointer_Type>
  ::std::ostream &operator<<(::std::ostream &stream, const memory_range_t<Pointer_Type> &range)
  {
    return operator<<(stream, range.template cast<void *>());
  }
  template <typename Pointer_Type>
  constexpr auto size(const memory_range_t<Pointer_Type> &range)
  {
    return range.size();
  }
}
