#pragma once
#include "vector_extrensic_allocator.hpp"
#include <functional>
namespace mcpputil
{
  template <class Key, typename Compare = ::std::less<>>
  class flat_set_extrensic_allocator_t : protected vector_extrensic_allocator_t<Key>
  {
  public:
    using key_type = Key;
    using value_type = Key;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = typename vector_extrensic_allocator_t<value_type>::iterator;
    using const_iterator = typename vector_extrensic_allocator_t<value_type>::const_iterator;
    using reverse_iterator = typename vector_extrensic_allocator_t<value_type>::reverse_iterator;
    using const_reverse_iterator = typename vector_extrensic_allocator_t<value_type>::const_reverse_iterator;
    using difference_type = typename vector_extrensic_allocator_t<value_type>::difference_type;
    using index_type = typename vector_extrensic_allocator_t<value_type>::index_type;
    using compare_type = Compare;

    using vector_extrensic_allocator_t<value_type>::begin;
    using vector_extrensic_allocator_t<value_type>::end;
    using vector_extrensic_allocator_t<value_type>::cbegin;
    using vector_extrensic_allocator_t<value_type>::cend;
    using vector_extrensic_allocator_t<value_type>::erase;
    using vector_extrensic_allocator_t<value_type>::size;
    using vector_extrensic_allocator_t<value_type>::empty;
    template <typename Allocator>
    std::pair<iterator, bool> insert(const value_type &value, Allocator &allocator);
    template <typename Allocator>
    std::pair<iterator, bool> insert(value_type &&value, Allocator &allocator);
    template <typename Allocator>
    iterator insert(const_iterator hint, const value_type &value, Allocator &allocator);
    template <typename Allocator>
    iterator insert(const_iterator hint, value_type &&value, Allocator &allocator);
    template <class InputIt, typename Allocator>
    void insert(InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    void insert(std::initializer_list<value_type> ilist, Allocator &allocator);
    template <typename Allocator, class... Args>
    std::pair<iterator, bool> emplace(Allocator &allocator, Args &&... args);
    template <typename Allocator, class... Args>
    iterator emplace_hint(Allocator &allocator, const_iterator hint, Args &&... args);
    template <typename Allocator>
    size_t erase(const key_type &key, Allocator &allocator);
    iterator find(const key_type &key);
    const_iterator find(const key_type &key) const;
    template <typename FK, typename = typename FK::is_transparent>
    iterator find(const FK &x);
    template <typename FK, typename = typename FK::is_transparent>
    const_iterator find(const FK &x) const;
    iterator lower_bound(const key_type &key);
    const_iterator lower_bound(const key_type &key) const;
    template <typename FK, typename = typename FK::is_transparent>
    iterator lower_bound(const FK &x);
    template <typename FK, typename = typename FK::is_transparent>
    const_iterator lower_bound(const FK &x) const;
    iterator upper_bound(const key_type &key);
    const_iterator upper_bound(const key_type &key) const;
    template <typename FK, typename = typename FK::is_transparent>
    iterator upper_bound(const FK &x);
    template <typename FK, typename = typename FK::is_transparent>
    const_iterator upper_bound(const FK &x) const;

  private:
    compare_type m_compare;
  };
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert(const value_type &value, Allocator &allocator)
      -> ::std::pair<iterator, bool>
  {
    auto it = lower_bound(value);
    if (!m_compare(value, *it))
      return ::std::make_pair(end(), false);
    vector_extrensic_allocator_t<key_type>::insert(it, value, allocator);
    return ::std::make_pair(it, true);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert(value_type &&value, Allocator &allocator)
      -> ::std::pair<iterator, bool>
  {
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert(const_iterator hint, const value_type &value, Allocator &allocator)
      -> iterator
  {
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert(const_iterator hint, value_type &&value, Allocator &allocator)
      -> iterator
  {
  }
  template <class Key, typename Compare>
  template <class InputIt, typename Allocator>
  void flat_set_extrensic_allocator_t<Key, Compare>::insert(InputIt first, InputIt last, Allocator &allocator)
  {
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  void flat_set_extrensic_allocator_t<Key, Compare>::insert(std::initializer_list<value_type> ilist, Allocator &allocator)
  {
  }
  template <class Key, typename Compare>
  template <typename Allocator, class... Args>
  auto flat_set_extrensic_allocator_t<Key, Compare>::emplace(Allocator &allocator, Args &&... args) -> ::std::pair<iterator, bool>
  {
  }
  template <class Key, typename Compare>
  template <typename Allocator, class... Args>
  auto flat_set_extrensic_allocator_t<Key, Compare>::emplace_hint(Allocator &allocator, const_iterator hint, Args &&... args)
      -> iterator
  {
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::erase(const key_type &key, Allocator &allocator) -> size_t
  {
    auto it = ::std::find(key);
    vector_extrensic_allocator_t<key_type>::erase(it, allocator);
    return 1;
  }

  template <class Key, typename Compare>
  auto flat_set_extrensic_allocator_t<Key, Compare>::find(const key_type &key) -> iterator
  {
    auto lb = lower_bound(key);
    if (*lb != key)
      return end();
    return lb;
  }
  template <class Key, typename Compare>
  auto flat_set_extrensic_allocator_t<Key, Compare>::find(const key_type &key) const -> const_iterator
  {
    auto lb = lower_bound(key);
    if (*lb != key)
      return end();
    return lb;
  }
  template <class Key, typename Compare>
  template <typename FK, typename>
  auto flat_set_extrensic_allocator_t<Key, Compare>::find(const FK &key) -> iterator
  {
    auto lb = lower_bound(key);
    if (*lb != key)
      return end();
    return lb;
  }
  template <class Key, typename Compare>
  template <typename FK, typename>
  auto flat_set_extrensic_allocator_t<Key, Compare>::find(const FK &key) const -> const_iterator
  {
    auto lb = lower_bound(key);
    if (*lb != key)
      return end();
    return lb;
  }
  template <class Key, typename Compare>
  auto flat_set_extrensic_allocator_t<Key, Compare>::lower_bound(const key_type &key) -> iterator
  {
    return ::std::lower_bound(begin(), end(), key, m_compare);
  }
  template <class Key, typename Compare>
  auto flat_set_extrensic_allocator_t<Key, Compare>::lower_bound(const key_type &key) const -> const_iterator
  {
    return ::std::lower_bound(begin(), end(), key, m_compare);
  }
  template <class Key, typename Compare>
  template <typename FK, typename>
  auto flat_set_extrensic_allocator_t<Key, Compare>::lower_bound(const FK &key) -> iterator
  {
    return ::std::lower_bound(begin(), end(), key, m_compare);
  }
  template <class Key, typename Compare>
  template <typename FK, typename>
  auto flat_set_extrensic_allocator_t<Key, Compare>::lower_bound(const FK &key) const -> const_iterator
  {
    return ::std::lower_bound(begin(), end(), key, m_compare);
  }
  template <class Key, typename Compare>
  auto flat_set_extrensic_allocator_t<Key, Compare>::upper_bound(const key_type &key) -> iterator
  {
    return ::std::upper_bound(begin(), end(), key, m_compare);
  }
  template <class Key, typename Compare>
  auto flat_set_extrensic_allocator_t<Key, Compare>::upper_bound(const key_type &key) const -> const_iterator
  {
    return ::std::upper_bound(begin(), end(), key, m_compare);
  }
  template <class Key, typename Compare>
  template <typename FK, typename>
  auto flat_set_extrensic_allocator_t<Key, Compare>::upper_bound(const FK &x) -> iterator
  {
    return ::std::upper_bound(begin(), end(), x, m_compare);
  }
  template <class Key, typename Compare>
  template <typename FK, typename>
  auto flat_set_extrensic_allocator_t<Key, Compare>::upper_bound(const FK &x) const -> const_iterator
  {
    return ::std::upper_bound(begin(), end(), x, m_compare);
  }
}
