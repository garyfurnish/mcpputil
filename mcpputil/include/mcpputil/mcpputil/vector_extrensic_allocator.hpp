#pragma once
#include "allocator.hpp"
#include <cstddef>
#include <gsl/gsl>
#include <iostream>
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

    static constexpr const difference_type cs_expansion_factor = 2;

    vector_extrensic_allocator_t();
    template <typename Allocator>
    explicit vector_extrensic_allocator_t(index_type count, Allocator &allocator);
    template <class InputIt, typename Allocator>
    vector_extrensic_allocator_t(InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    vector_extrensic_allocator_t(const vector_extrensic_allocator_t &other, Allocator &alloc);
    vector_extrensic_allocator_t(vector_extrensic_allocator_t &&other);
    template <typename Allocator>
    vector_extrensic_allocator_t(std::initializer_list<T> init, Allocator &alloc);
    template <typename Allocator>
    void destroy(Allocator &allocator);
    ~vector_extrensic_allocator_t();

    template <typename Allocator>
    void assign(index_type count, const T &value, Allocator &allocator);
    template <class InputIt, typename Allocator, typename = typename ::std::iterator_traits<InputIt>::iterator_category>
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
    template <typename Allocator>
    void reserve_expand(index_type new_cap, Allocator &allocator);
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
    template <class InputIt, typename Allocator, typename = typename ::std::iterator_traits<InputIt>::iterator_category>
    iterator insert(const_iterator pos, InputIt first, InputIt last, Allocator &allocator);
    template <typename Allocator>
    iterator insert(const_iterator pos, std::initializer_list<T> ilist, Allocator &allocator);
    template <typename Allocator, class... Args>
    iterator emplace(const_iterator pos, Allocator &allocator, Args &&... args);
    template <typename Allocator>
    iterator erase(const_iterator pos, Allocator &allocator);
    template <typename Allocator>
    iterator erase(const_iterator first, const_iterator last, Allocator &allocator);
    template <typename Allocator>
    void push_back(const T &value, Allocator &allocator);
    template <typename Allocator>
    void push_back(T &&value, Allocator &allocator);
    template <typename Allocator, class... Args>
    reference emplace_back(Allocator &allocator, Args &&... args);
    template <typename Allocator>
    void pop_back(Allocator &allocator);
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
  template <typename Allocator>
  vector_extrensic_allocator_t<T>::vector_extrensic_allocator_t(index_type count, Allocator &allocator)
      : vector_extrensic_allocator_t()
  {
    resize(count, allocator);
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
    assign(init, allocator);
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::destroy(Allocator &allocator)
  {
    if (m_data == nullptr) {
      return;
    }
    clear(allocator);
    ::std::allocator_traits<Allocator>::deallocate(allocator, m_data, ::gsl::narrow_cast<size_t>(m_capacity));
    m_data = nullptr;
    m_size = m_capacity = 0;
  }
  template <typename T>
  vector_extrensic_allocator_t<T>::~vector_extrensic_allocator_t()
  {
    assert(!m_data);
  }

  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::assign(index_type count, const T &value, Allocator &allocator)
  {
    clear(allocator);
    reserve_expand(count, allocator);
    m_size = count;
    ::std::uninitialized_fill_n(m_data, count, value);
  }
  template <typename T>
  template <class InputIt, typename Allocator, typename>
  void vector_extrensic_allocator_t<T>::assign(InputIt first, InputIt last, Allocator &allocator)
  {
    clear(allocator);
    for (auto it = first; it != last; ++it) {
      push_back(*it, allocator);
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
    auto new_pointer = ::std::allocator_traits<Allocator>::allocate(allocator, ::gsl::narrow<size_t>(new_cap));
    move_uninitialized(begin(), end(), new_pointer);
    ::std::allocator_traits<Allocator>::deallocate(allocator, m_data, ::gsl::narrow_cast<size_t>(m_capacity));
    m_capacity = new_cap;
    m_data = new_pointer;
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::reserve_expand(index_type new_cap, Allocator &allocator)
  {
    reserve(::std::max(new_cap, capacity() * cs_expansion_factor), allocator);
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
    mcpputil::destroy(begin(), end(), allocator);
    m_size = 0;
  }
  template <typename T>
  template <typename Allocator>
  auto vector_extrensic_allocator_t<T>::insert(const_iterator pos, const T &value, Allocator &allocator) -> iterator
  {
    auto index = pos - begin();
    reserve_expand(size() + 1, allocator);
    auto new_pos = begin() + index;
    uninitialied_shift_by_n_pos(new_pos, end(), 1, allocator);
    ::std::allocator_traits<Allocator>::construct(allocator, new_pos, value);
    m_size++;
    return new_pos;
  }
  template <typename T>
  template <typename Allocator>
  auto vector_extrensic_allocator_t<T>::insert(const_iterator pos, T &&value, Allocator &allocator) -> iterator
  {
    auto index = pos - begin();
    reserve_expand(size() + 1, allocator);
    auto new_pos = begin() + index;
    uninitialied_shift_by_n_pos(new_pos, end(), 1, allocator);
    ::std::allocator_traits<Allocator>::construct(allocator, new_pos, value);
    m_size++;
    return new_pos;
  }
  template <typename T>
  template <typename Allocator>
  auto vector_extrensic_allocator_t<T>::insert(const_iterator pos, index_type count, const T &value, Allocator &allocator)
      -> iterator
  {
    auto index = pos - begin();
    reserve_expand(size() + count, allocator);
    auto new_pos = begin() + index;
    uninitialied_shift_by_n_pos(new_pos, end() + count - 1, count, allocator);
    uninitialized_fill_n(new_pos, count, value, allocator);
    m_size += count;
    return new_pos;
  }
  template <typename T>
  template <class InputIt, typename Allocator, typename>
  auto vector_extrensic_allocator_t<T>::insert(const_iterator pos, InputIt first, InputIt last, Allocator &allocator) -> iterator
  {
    auto index = pos - begin();
    auto count = last - first;
    reserve_expand(size() + count, allocator);
    auto new_pos = begin() + index;
    uninitialied_shift_by_n_pos(new_pos, end() + count - 1, count, allocator);
    uninitialized_copy_n(first, last - first, new_pos, allocator);
    m_size += last - first;
    return new_pos;
  }
  template <typename T>
  template <typename Allocator>
  auto vector_extrensic_allocator_t<T>::insert(const_iterator pos, std::initializer_list<T> ilist, Allocator &allocator)
      -> iterator
  {
    return insert(pos, ilist.begin(), ilist.end(), allocator);
  }
  template <typename T>
  template <typename Allocator, class... Args>
  auto vector_extrensic_allocator_t<T>::emplace(const_iterator pos, Allocator &allocator, Args &&... args) -> iterator
  {
    auto index = pos - begin();
    reserve_expand(size() + 1, allocator);
    auto new_pos = begin() + index;
    uninitialied_shift_by_n_pos(new_pos, end(), 1, allocator);
    ::std::allocator_traits<Allocator>::construct(allocator, new_pos, ::std::forward<Args...>(args...));
    m_size++;
    return new_pos;
  }
  template <typename T>
  template <typename Allocator>
  auto vector_extrensic_allocator_t<T>::erase(const_iterator pos, Allocator &allocator) -> iterator
  {
    ::std::allocator_traits<Allocator>::destroy(allocator, pos);
    uninitialized_shift_by_n_neg(pos, end(), 1, allocator);
    m_size--;
    auto offset = pos - begin();
    return begin() + offset;
  }
  template <typename T>
  template <typename Allocator>
  auto vector_extrensic_allocator_t<T>::erase(const_iterator first, const_iterator last, Allocator &allocator) -> iterator
  {
    auto count = last - first;
    mcpputil::destroy(first, last, allocator);
    uninitialized_shift_by_n_neg(first, end(), count, allocator);
    m_size -= count;
    return begin() + (first - begin());
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::push_back(const T &value, Allocator &allocator)
  {
    emplace(end(), allocator, value);
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::push_back(T &&value, Allocator &allocator)
  {
    emplace(end(), allocator, ::std::move(value));
  }
  template <typename T>
  template <typename Allocator, class... Args>
  auto vector_extrensic_allocator_t<T>::emplace_back(Allocator &allocator, Args &&... args) -> reference
  {
    auto old_end = end();
    emplace(end(), allocator, ::std::forward<Args...>(args...));
    return *old_end;
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::pop_back(Allocator &allocator)
  {
    ::std::allocator_traits<Allocator>::destroy(allocator, end() - 1);
    --m_size;
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::resize(index_type count, Allocator &allocator)
  {
    auto num = count - size();
    if (num == 0) {
      return;
    }
    if (num < 0) {
      // shrink
      erase(end() + num, end(), allocator);
    } else {
      // grow
      reserve_expand(count, allocator);
      uninitialized_default_construct_n(end(), count, allocator);
      m_size = count;
    }
  }
  template <typename T>
  template <typename Allocator>
  void vector_extrensic_allocator_t<T>::resize(index_type count, const value_type &value, Allocator &allocator)
  {
    auto num = count - size();
    if (num == 0) {
      return;
    }

    if (num < 0) {
      // shrink
      erase(end() + num, end(), allocator);
    } else {
      // grow
      reserve_expand(count, allocator);
      uninitialized_fill_n(end(), count, value, allocator);
      m_size = count;
    }
  }
  template <typename T>
  void vector_extrensic_allocator_t<T>::swap(vector_extrensic_allocator_t &other)
  {
    using ::std::swap;
    swap(m_data, other.m_data);
    swap(m_size, other.m_size);
    swap(m_capacity, other.m_capacity);
  }
}
