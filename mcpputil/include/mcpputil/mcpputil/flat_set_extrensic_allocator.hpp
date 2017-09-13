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
    using vector_extrensic_allocator_t<value_type>::capacity;
    using vector_extrensic_allocator_t<value_type>::empty;
    using vector_extrensic_allocator_t<value_type>::destroy;

    flat_set_extrensic_allocator_t() = default;
    explicit flat_set_extrensic_allocator_t(const Compare &comp);
    template <typename InputIt, typename Allocator, typename = typename ::std::iterator_traits<InputIt>::iterator_category>
    flat_set_extrensic_allocator_t(InputIt first, InputIt last, Allocator &alloc, const compare_type &comp = compare_type{});
    template <typename Allocator>
    flat_set_extrensic_allocator_t(const flat_set_extrensic_allocator_t &other, Allocator &alloc);
    template <typename Allocator>
    flat_set_extrensic_allocator_t(flat_set_extrensic_allocator_t &&other);
    template <typename Allocator>
    flat_set_extrensic_allocator_t(std::initializer_list<value_type> init,
                                   Allocator &alloc,
                                   const compare_type &comp = compare_type{});

    template <typename Allocator>
    std::pair<iterator, bool> insert(const value_type &value, Allocator &allocator);
    template <typename Allocator>
    std::pair<iterator, bool> insert(value_type &&value, Allocator &allocator);
    template <typename Allocator>
    std::pair<iterator, bool> insert_search(const_iterator hint, const value_type &value, Allocator &allocator);
    template <typename Allocator>
    ::std::pair<iterator, bool> insert_search(const_iterator hint, value_type &&value, Allocator &allocator);
    template <typename Allocator>
    std::pair<iterator, bool> insert(const_iterator hint, const value_type &value, Allocator &allocator);
    template <typename Allocator>
    ::std::pair<iterator, bool> insert(const_iterator hint, value_type &&value, Allocator &allocator);

    template <typename InputIt, typename Allocator>
    void insert(InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    void insert(std::initializer_list<value_type> ilist, Allocator &allocator);
    template <typename InputIt, typename Allocator>
    void insert_sorted_contiguous(InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    size_t erase(const key_type &key, Allocator &allocator);
    iterator find(const key_type &key);
    const_iterator find(const key_type &key) const;
    template <typename FK, typename = typename FK::is_transparent>
    iterator find(const FK &key);
    template <typename FK, typename = typename FK::is_transparent>
    const_iterator find(const FK &key) const;
    iterator lower_bound(const key_type &key);
    const_iterator lower_bound(const key_type &key) const;
    template <typename FK, typename = typename FK::is_transparent>
    iterator lower_bound(const FK &key);
    template <typename FK, typename = typename FK::is_transparent>
    const_iterator lower_bound(const FK &key) const;
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
  flat_set_extrensic_allocator_t<Key, Compare>::flat_set_extrensic_allocator_t(const Compare &comp) : m_compare(comp)
  {
  }
  template <class Key, typename Compare>
  template <typename InputIt, typename Allocator, typename>
  flat_set_extrensic_allocator_t<Key, Compare>::flat_set_extrensic_allocator_t(InputIt first,
                                                                               InputIt last,
                                                                               Allocator &alloc,
                                                                               const compare_type &comp)
      : m_compare(comp)
  {
    insert(first, last, alloc);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  flat_set_extrensic_allocator_t<Key, Compare>::flat_set_extrensic_allocator_t(const flat_set_extrensic_allocator_t &other,
                                                                               Allocator &alloc)
      : vector_extrensic_allocator_t<value_type>(other, alloc), m_compare(other.m_compare)
  {
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  flat_set_extrensic_allocator_t<Key, Compare>::flat_set_extrensic_allocator_t(flat_set_extrensic_allocator_t &&other)
      : vector_extrensic_allocator_t<value_type>(::std::move(other)), m_compare(::std::move(other.m_compare))
  {
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  flat_set_extrensic_allocator_t<Key, Compare>::flat_set_extrensic_allocator_t(std::initializer_list<value_type> init,
                                                                               Allocator &alloc,
                                                                               const compare_type &comp)
      : m_compare(comp)
  {
    insert(init, alloc);
  }

  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert(const value_type &value, Allocator &allocator)
      -> ::std::pair<iterator, bool>
  {
    if (empty()) {
      this->push_back(value, allocator);
      return ::std::make_pair(begin(), false);
    }
    auto it = lower_bound(value);
    if (it != end() && !m_compare(value, *it)) {
      return ::std::make_pair(end(), false);
    }
    it = vector_extrensic_allocator_t<key_type>::insert(it, value, allocator);
    return ::std::make_pair(it, true);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert(value_type &&value, Allocator &allocator)
      -> ::std::pair<iterator, bool>
  {
    if (empty()) {
      this->emplace_back(allocator, value);
      return ::std::make_pair(begin(), false);
    }
    auto it = lower_bound(value);
    if (it != end() && !m_compare(value, *it)) {
      return ::std::make_pair(end(), false);
    }
    it = vector_extrensic_allocator_t<key_type>::emplace(it, allocator, value);
    return ::std::make_pair(it, true);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert_search(const_iterator hint,
                                                                   const value_type &value,
                                                                   Allocator &allocator) -> std::pair<iterator, bool>
  {
    auto it = end();
    if (!empty()) {
      it = ::std::lower_bound(const_cast<iterator>(hint), end(), value);
      if (it != end() && !m_compare(value, *it)) {
        return ::std::make_pair(end(), false);
      }
    }
    it = vector_extrensic_allocator_t<key_type>::insert(it, value, allocator);
    return ::std::make_pair(it, true);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert_search(const_iterator hint, value_type &&value, Allocator &allocator)
      -> ::std::pair<iterator, bool>
  {
    auto it = end();
    if (!empty()) {
      it = ::std::lower_bound(const_cast<iterator>(hint), end(), value);
      if (it != end() && !m_compare(value, *it)) {
        return ::std::make_pair(end(), false);
      }
    }
    it = vector_extrensic_allocator_t<key_type>::emplace(it, allocator, ::std::move(value));
    return ::std::make_pair(it, true);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert(const_iterator hint, const value_type &value, Allocator &allocator)
      -> std::pair<iterator, bool>
  {
    if (!empty()) {
      if (hint != end() && hint != begin() && !m_compare(*(hint - 1), value)) {
        return insert(value, allocator);
      }
      if (hint != end() && !m_compare(value, *(hint))) {
        return insert(value, allocator);
      }
      if (!m_compare(value, *hint) && !m_compare(*hint, value)) {
        return ::std::make_pair(end(), false);
      }
    }
    auto it = vector_extrensic_allocator_t<key_type>::insert(hint, value, allocator);
    return ::std::make_pair(it, true);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::insert(const_iterator hint, value_type &&value, Allocator &allocator)
      -> ::std::pair<iterator, bool>
  {
    if (!empty()) {
      if (hint != end() && hint != begin() && !m_compare(*(hint - 1), value)) {
        return insert(value, allocator);
      }
      if (hint != end() && !m_compare(value, *(hint))) {
        return insert(value, allocator);
      }
      if (!m_compare(value, *hint) && !m_compare(*hint, value)) {
        return ::std::make_pair(end(), false);
      }
    }
    auto it = vector_extrensic_allocator_t<key_type>::emplace(hint, allocator, ::std::move(value));
    return ::std::make_pair(it, true);
  }
  template <class Key, typename Compare>
  template <typename InputIt, typename Allocator>
  void flat_set_extrensic_allocator_t<Key, Compare>::insert(InputIt first, InputIt last, Allocator &allocator)
  {
    for (auto it = first; it != last; ++it) {
      insert(*it, allocator);
    }
  }
  template <class Key, typename Compare>
  template <typename InputIt, typename Allocator>
  void flat_set_extrensic_allocator_t<Key, Compare>::insert_sorted_contiguous(InputIt first, InputIt last, Allocator &allocator)
  {
    if (first == last) {
      return;
    }
    auto it = end();
    if (!empty()) {
      it = lower_bound(*first);
      if (it != end() && !m_compare(*first, *it)) {
        return;
      }
    }
    vector_extrensic_allocator_t<key_type>::insert(it, first, last, allocator);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  void flat_set_extrensic_allocator_t<Key, Compare>::insert(std::initializer_list<value_type> ilist, Allocator &allocator)
  {
    insert(ilist.begin(), ilist.end(), allocator);
  }
  template <class Key, typename Compare>
  template <typename Allocator>
  auto flat_set_extrensic_allocator_t<Key, Compare>::erase(const key_type &key, Allocator &allocator) -> size_t
  {
    auto it = find(key);
    vector_extrensic_allocator_t<key_type>::erase(it, allocator);
    return 1;
  }

  template <class Key, typename Compare>
  auto flat_set_extrensic_allocator_t<Key, Compare>::find(const key_type &key) -> iterator
  {
    auto lb = lower_bound(key);
    if (*lb != key) {
      return end();
    }
    return lb;
  }
  template <class Key, typename Compare>
  auto flat_set_extrensic_allocator_t<Key, Compare>::find(const key_type &key) const -> const_iterator
  {
    auto lb = lower_bound(key);
    if (*lb != key) {
      return end();
    }
    return lb;
  }
  template <class Key, typename Compare>
  template <typename FK, typename>
  auto flat_set_extrensic_allocator_t<Key, Compare>::find(const FK &key) -> iterator
  {
    auto lb = lower_bound(key);
    if (*lb != key) {
      return end();
    }
    return lb;
  }
  template <class Key, typename Compare>
  template <typename FK, typename>
  auto flat_set_extrensic_allocator_t<Key, Compare>::find(const FK &key) const -> const_iterator
  {
    auto lb = lower_bound(key);
    if (*lb != key) {
      return end();
    }
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
} // namespace mcpputil
