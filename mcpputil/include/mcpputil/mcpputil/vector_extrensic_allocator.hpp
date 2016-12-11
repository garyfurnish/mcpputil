#pragma once
#include "allocator.hpp"
#include <cstddef>
#include <iterator>
#include <limits>
#include <utility>
namespace mcpputil
{
  template <typename T>
  class vector_extrensic_allocator_t
  {
  public:
    using value_type = T;
    using index_type = ptrdiff_t;
    using difference_type = ptrdiff_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = ::std::reverse_iterator<iterator>;
    using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;

    vector_extrensic_allocator_t();
    explicit vector_extrensic_allocator_t(index_type count);
    template <class InputIt, typename Allocator>
    vector_extrensic_allocator_t(InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    vector_extrensic_allocator_t(const vector_extrensic_allocator_t &other, Allocator &alloc);
    vector_extrensic_allocator_t(vector_extrensic_allocator_t &&other);
    template <typename Allocator>
    vector_extrensic_allocator_t(std::initializer_list<T> init, Allocator &alloc);

    template <typename Allocator>
    void assign(index_type count, const T &value, Allocator &allocator);
    template <class InputIt, typename Allocator>
    void assign(InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    void assign(std::initializer_list<T> ilist, Allocator &allocator);
    reference at(index_type pos);
    const_reference at(index_type pos) const;
    reference operator[](index_type pos);
    const_reference operator[](index_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T *data();
    const T *data() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    bool empty() const;
    index_type size() const;
    index_type max_size() const;
    template <typename Allocator>
    void reserve(index_type new_cap, Allocator &allocator);
    index_type capacity() const;
    template <typename Allocator>
    void shrink_to_fit(Allocator &allocator);

    template <typename Allocator>
    void clear(Allocator &allocator);
    template <typename Allocator>
    iterator insert(const_iterator pos, const T &value, Allocator &allocator);
    template <typename Allocator>
    iterator insert(const_iterator pos, T &&value, Allocator &allocator);
    template <typename Allocator>
    iterator insert(const_iterator pos, index_type count, const T &value, Allocator &allocator);
    template <class InputIt, typename Allocator>
    iterator insert(const_iterator pos, InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    iterator insert(const_iterator pos, std::initializer_list<T> ilist, Allocator &allocator);
    template <typename Allocator, class... Args>
    iterator emplace(const_iterator pos, Args &&... args, Allocator &allocator);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    template <typename Allocator>
    void push_back(const T &value, Allocator &allocator);
    template <typename Allocator>
    void push_back(T &&value, Allocator &allocator);
    template <typename Allocator, class... Args>
    reference emplace_back(Allocator &allocator, Args &&... args);
    void pop_back();
    template <typename Allocator>
    void resize(index_type count, Allocator &allocator);
    template <typename Allocator>
    void resize(index_type count, const value_type &value, Allocator &allocator);
    void swap(vector_extrensic_allocator_t &other);

  private:
    pointer m_data;
    difference_type m_size;
    difference_type m_capacity;
  };
  template <typename T>
  vector_extrensic_allocator_t<T>::vector_extrensic_allocator_t() : m_data(nullptr), m_size(0), m_capacity(0)
  {
  }
  template <typename T>
  vector_extrensic_allocator_t<T>::vector_extrensic_allocator_t(index_type count) : vector_extrensic_allocator_t()
  {
    resize(count);
  }
  template <typename T>
  template <class InputIt, typename Allocator>
  vector_extrensic_allocator_t<T>::vector_extrensic_allocator_t(InputIt first, InputIt last, Allocator &allocator)
      : vector_extrensic_allocator_t()
  {
    assign(first, last, allocator);
  }
  template <typename T>
  template <typename Allocator>
  vector_extrensic_allocator_t<T>::vector_extrensic_allocator_t(const vector_extrensic_allocator_t &other, Allocator &allocator)
      : vector_extrensic_allocator_t()
  {
    assign(other.begin(), other.end(), allocator);
  }
  template <typename T>
  vector_extrensic_allocator_t<T>::vector_extrensic_allocator_t(vector_extrensic_allocator_t &&other)
      : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
  {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
  }
  template <typename T>
  template <typename Allocator>
  vector_extrensic_allocator_t<T>::vector_extrensic_allocator_t(std::initializer_list<T> init, Allocator &allocator)
      : vector_extrensic_allocator_t()
  {
    assign(init.begin(), init.end(), allocator);
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::assign(index_type count, const T &value, Allocator &allocator)
  {
    clear(allocator);
    resize(count);
    m_size = count;
    ::std::uninitialized_fill_n(m_data, count, value);
  }
  template <typename T>
  template <class InputIt, typename Allocator>
  void vector_extrensic_allocator_t<T>::assign(InputIt first, InputIt last, Allocator &allocator)
  {
    clear(allocator);
    auto it = first;
    while (it != last) {
      push_back(*it);
    }
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::assign(std::initializer_list<T> ilist, Allocator &allocator)
  {
    assign(ilist.begin(), ilist.end(), allocator);
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::at(index_type pos) -> reference
  {
    if (pos >= size())
      throw ::std::out_of_range("");
    return m_data[pos];
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::at(index_type pos) const -> const_reference
  {
    if (pos >= size())
      throw ::std::out_of_range("");
    return m_data[pos];
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::operator[](index_type pos) -> reference
  {
    return m_data[pos];
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::operator[](index_type pos) const -> const_reference
  {
    return m_data[pos];
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::front() -> reference
  {
    return m_data[0];
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::front() const -> const_reference
  {
    return m_data[0];
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::back() -> reference
  {
    return m_data[m_size - 1];
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::back() const -> const_reference
  {
    return m_data[m_size - 1];
  }
  template <typename T>
  T *vector_extrensic_allocator_t<T>::data()
  {
    return m_data;
  }
  template <typename T>
  const T *vector_extrensic_allocator_t<T>::data() const
  {
    return m_data;
  }

  template <typename T>
  auto vector_extrensic_allocator_t<T>::begin() -> iterator
  {
    return m_data;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::begin() const -> const_iterator
  {
    return m_data;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::cbegin() const -> const_iterator
  {
    return m_data;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::end() -> iterator
  {
    return m_data + m_size;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::end() const -> const_iterator
  {
    return m_data + m_size;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::cend() const -> const_iterator
  {
    return m_data + m_size;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::rbegin() -> reverse_iterator
  {
    return ::std::make_reverse_iterator(end());
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::rbegin() const -> const_reverse_iterator
  {
    return ::std::make_reverse_iterator(end());
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::crbegin() const -> const_reverse_iterator
  {
    return ::std::make_reverse_iterator(end());
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::rend() -> reverse_iterator
  {
    return ::std::make_reverse_iterator(begin());
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::rend() const -> const_reverse_iterator
  {
    return ::std::make_reverse_iterator(begin());
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::crend() const -> const_reverse_iterator
  {
    return ::std::make_reverse_iterator(begin());
  }
  template <typename T>
  bool vector_extrensic_allocator_t<T>::empty() const
  {
    return m_size == 0;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::size() const -> index_type
  {
    return m_size;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::max_size() const -> index_type
  {
    return ::std::numeric_limits<index_type>::max();
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::reserve(index_type new_cap, Allocator &allocator)
  {
    if (new_cap <= m_capacity) {
      return;
    }
    auto new_pointer = ::std::allocator_traits<Allocator>::allocate(allocator, new_cap);
    move_uninitialized(begin(), end(), new_pointer);
    ::std::allocator_traits<Allocator>::deallocate(allocator, m_data, m_capacity);
    m_capacity = new_cap;
    m_data = new_pointer;
  }
  template <typename T>
  auto vector_extrensic_allocator_t<T>::capacity() const -> index_type
  {
    return m_capacity;
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::shrink_to_fit(Allocator &allocator)
  {
    auto new_cap = size();
    auto new_pointer = ::std::allocator_traits<Allocator>::allocate(allocator, new_cap);
    move_uninitialized(begin(), end(), new_pointer);
    ::std::allocator_traits<Allocator>::deallocate(allocator, m_data, m_capacity);
    m_capacity = new_cap;
    m_data = new_pointer;
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::clear(Allocator &allocator)
  {
    destroy(begin(), end(), allocator);
    m_size = 0;
  }
}
