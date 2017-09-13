#pragma once
#include "declarations.hpp"
#include <limits>
#include <memory>
#include <tuple>
#include <utility>
namespace mcpputil
{

  template <typename Pointer_Type>
  class memory_range_t : public ::std::tuple<Pointer_Type, Pointer_Type>
  {
  public:
    using this_type = memory_range_t<Pointer_Type>;
    using pointer_type = Pointer_Type;
    using difference_type = typename ::std::pointer_traits<pointer_type>::difference_type;
    using size_type = size_t;
    using ::std::tuple<Pointer_Type, Pointer_Type>::tuple;

    memory_range_t() noexcept(::std::is_nothrow_move_constructible<pointer_type>::value);
    void set_begin(pointer_type begin) noexcept(::std::is_nothrow_move_assignable<pointer_type>::value);
    void set_end(pointer_type end) noexcept(::std::is_nothrow_move_assignable<pointer_type>::value);
    void set(pointer_type begin, pointer_type end) noexcept(::std::is_nothrow_move_assignable<pointer_type>::value);
    void set(::std::pair<pointer_type, pointer_type> pair) noexcept(::std::is_nothrow_move_assignable<pointer_type>::value);

    constexpr auto begin() const noexcept(::std::is_nothrow_copy_constructible<pointer_type>::value) -> pointer_type;
    constexpr auto end() const noexcept(::std::is_nothrow_copy_constructible<pointer_type>::value) -> pointer_type;
    constexpr auto size() const noexcept -> size_type;
    constexpr auto empty() const noexcept -> bool;

    constexpr auto contains(const pointer_type &ptr) const noexcept -> bool;
    constexpr auto contains(const memory_range_t<pointer_type> &) const noexcept -> bool;
    template <typename T>
    constexpr auto contains(T &&t) const noexcept -> bool;

    template <typename New_Pointer_Type>
    constexpr auto cast() const noexcept -> memory_range_t<New_Pointer_Type>;

    constexpr static auto size_comparator() noexcept
    {
      return [](const memory_range_t<pointer_type> &a, const memory_range_t<pointer_type> &b) noexcept->bool
      {
        return a.size() < b.size();
      };
    }
    ::std::tuple<pointer_type, pointer_type> as_tuple() const
    {
      return *this;
    }
  };
  template <typename Pointer_Type>
  constexpr auto operator==(const memory_range_t<Pointer_Type> &lhs, const memory_range_t<Pointer_Type> &rhs) noexcept -> bool;
  template <typename Pointer_Type>
  constexpr auto operator!=(const memory_range_t<Pointer_Type> &lhs, const memory_range_t<Pointer_Type> &rhs) noexcept -> bool;
  template <typename Pointer_Type>
  constexpr auto operator<(const memory_range_t<Pointer_Type> &lhs, const memory_range_t<Pointer_Type> &rhs) noexcept -> bool;

  template <typename Pointer_Type>
  ::std::ostream &operator<<(::std::ostream &stream, const memory_range_t<Pointer_Type> &range);
  template <>
  MCPPUTIL_DLL_PUBLIC::std::ostream &operator<<(::std::ostream &stream, const memory_range_t<void *> &range);
  using system_memory_range_t = memory_range_t<uint8_t *>;
} // namespace mcpputil
#include "memory_range_impl.hpp"
