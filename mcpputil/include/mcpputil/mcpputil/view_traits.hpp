#pragma once
#include <iterator>
namespace mcpputil
{
  /**
   * \brief Traits for objects that have a view like interface (including containers).
   **/
  template <typename T>
  class view_traits_t
  {
  public:
    /**
     * \brief This is a replacement for size_type.
     *
     * This can be signed.
     **/
    using index_type = decltype(::std::declval<T>().size());
    using difference_type = typename ::std::iterator_traits<typename T::iterator>::difference_type;
  };
}
