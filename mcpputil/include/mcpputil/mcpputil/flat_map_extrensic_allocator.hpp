#pragma once
#include "vector_extrensic_allocator.hpp"
#include <functional>
#include <vector>
namespace mcpputil
{
  template <class K, class V, typename Compare = ::std::less<>>
  class flat_map_extrensic_allocator_t : protected vector_extrensic_allocator_t<::std::pair<K, V>>
  {
  public:
    using key_type = K;
    using mapped_type = V;
    using value_type = typename ::std::pair<K, V>;
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
    using vector_extrensic_allocator_t<::std::pair<K, V>>::vector;

    flat_map_extrensic_allocator_t();
    explicit flat_map_extrensic_allocator_t(const compare_type &comp);
    template <class InputIterator, typename Allocator>
    flat_map_extrensic_allocator_t(InputIterator first,
                                   InputIterator last,
                                   Allocator &allocator,
                                   const compare_type &comp = compare_type());
    template <class InputIterator, typename Allocator>
    flat_map_extrensic_allocator_t(InputIterator first, InputIterator last, Allocator &alloc);
    flat_map_extrensic_allocator_t(const flat_map_extrensic_allocator_t &other);

    flat_map_extrensic_allocator_t(flat_map_extrensic_allocator_t &&other);
    template <typename Allocator>
    flat_map_extrensic_allocator_t(std::initializer_list<value_type> init,
                                   Allocator &allocator,
                                   const compare_type &comp = compare_type());
    template <typename Allocator>
    flat_map_extrensic_allocator_t(std::initializer_list<value_type> init, const Allocator &);
    ~flat_map_extrensic_allocator_t();
    template <typename K_, typename V_>
    friend bool operator==(const flat_map_extrensic_allocator_t<K_, V_> &rhs, const flat_map_extrensic_allocator_t<K_, V_> &lhs);
    template <typename K_, typename V_>
    friend bool operator!=(const flat_map_extrensic_allocator_t<K_, V_> &rhs, const flat_map_extrensic_allocator_t<K_, V_> &lhs);

    value_type &at(const key_type &key);
    const value_type &at(const key_type &key) const;
    template <typename Allocator>
    std::pair<iterator, bool> insert(const value_type &value, Allocator &allocator);
    template <class P, typename Allocator>
    std::pair<iterator, bool> insert(P &&value, Allocator &allocator);
    template <typename Allocator>
    std::pair<iterator, bool> insert(value_type &&value, Allocator &allocator);
    template <class InputIt, typename Allocator>
    void insert(InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    void insert(std::initializer_list<value_type> ilist, Allocator &allocator);
    template <class M, typename Allocator>
    ::std::pair<iterator, bool> insert_or_assign(const key_type &k, M &&obj, Allocator &allocator);
    template <class M, typename Allocator>
    ::std::pair<iterator, bool> insert_or_assign(key_type &&k, M &&obj, Allocator &allocator);
    template <class M, typename Allocator>
    iterator insert_or_assign(const_iterator hint, const key_type &k, M &&obj, Allocator &allocator);
    template <class M, typename Allocator>
    iterator insert_or_assign(const_iterator hint, key_type &&k, M &&obj, Allocator &);
    template <typename Allocator, class... Args>
    std::pair<iterator, bool> emplace(Allocator &allocator, Args &&... args);
    template <typename Allocator, class... Args>
    ::std::pair<iterator, bool> try_emplace(Allocator &allocator, const key_type &k, Args &&... args);
    template <typename Allocator, class... Args>
    ::std::pair<iterator, bool> try_emplace(Allocator &allocator, key_type &&k, Args &&... args);
    template <typename Allocator, class... Args>
    iterator try_emplace(Allocator &allocator, const_iterator hint, const key_type &k, Args &&... args);
    template <typename Allocator, class... Args>
    iterator try_emplace(Allocator &allocator, const_iterator hint, key_type &&k, Args &&... args);
    iterator find(const key_type &key);
    const_iterator find(const key_type &key) const;
    template <class FK>
    iterator find(const FK &x);
    template <class FK>
    const_iterator find(const FK &x) const;
    iterator lower_bound(const key_type &key);
    const_iterator lower_bound(const key_type &key) const;
    template <class FK>
    iterator lower_bound(const FK &x);
    template <class FK>
    const_iterator lower_bound(const FK &x) const;
    iterator upper_bound(const key_type &key);
    const_iterator upper_bound(const key_type &key) const;
    template <class FK>
    iterator upper_bound(const K &x);
    template <class FK>
    const_iterator upper_bound(const K &x) const;
  };
  template <typename K_, typename V_>
  bool operator==(const flat_map_extrensic_allocator_t<K_, V_> &rhs, const flat_map_extrensic_allocator_t<K_, V_> &lhs)
  {
    return static_cast<const vector_extrensic_allocator_t<::std::pair<K_, V_>> &>(rhs) ==
           static_cast<const vector_extrensic_allocator_t<::std::pair<K_, V_>> &>(lhs);
  }
  template <typename K_, typename V_>
  bool operator!=(const flat_map_extrensic_allocator_t<K_, V_> &rhs, const flat_map_extrensic_allocator_t<K_, V_> &lhs)
  {
    return static_cast<const vector_extrensic_allocator_t<::std::pair<K_, V_>> &>(rhs) !=
           static_cast<const vector_extrensic_allocator_t<::std::pair<K_, V_>> &>(lhs);
  }
}
