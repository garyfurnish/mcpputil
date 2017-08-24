#pragma once
#include "declarations.hpp"
namespace mcpputil
{
  /**
   * \brief Singleton CRTP class.
   **/
  template <typename T>
  class MCPPUTIL_PUBLIC singleton_t
  {
  public:
    /**
     * \brief Initialize the singleton.
     **/
    singleton_t() noexcept;
    singleton_t(const singleton_t<T> &) = delete;
    singleton_t(singleton_t<T> &&) = delete;
    /**
     * \brief Destructor for the singleton.
     **/
    ~singleton_t();
    singleton_t<T> &operator=(const singleton_t<T> &) = delete;
    singleton_t<T> &operator=(singleton_t<T> &&) = delete;
    static T *get_singleton_pointer() noexcept;
    static T &get_singleton() noexcept;
    static T &gs() noexcept;
    static T *gsp() noexcept;

  private:
    /**
    Internal pointer to singleton.
    **/
    static T *s_s;
  };
  template <typename T>
  singleton_t<T>::singleton_t() noexcept
  {
    if (s_s) {
      abort();
    }
    s_s = static_cast<T *>(this);
  }
  template <typename T>
  singleton_t<T>::~singleton_t()
  {
    s_s = nullptr;
  }
  template <typename T>
  T *singleton_t<T>::get_singleton_pointer() noexcept
  {
    return s_s;
  }
  template <typename T>
  T &singleton_t<T>::get_singleton() noexcept
  {
    return *s_s;
  }
  template <typename T>
  T &singleton_t<T>::gs() noexcept
  {
    return *s_s;
  }
  template <typename T>
  T *singleton_t<T>::gsp() noexcept
  {
    return s_s;
  }
}
