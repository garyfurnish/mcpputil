#pragma once
namespace mcpputil
{
  /**
   * \brief Make a reverse iterator from an iterator.
   **/
  template <class Iterator>
  ::std::reverse_iterator<Iterator> make_reverse_iterator(Iterator i)
  {
    return ::std::reverse_iterator<Iterator>(i);
  }
} // namespace mcpputil
