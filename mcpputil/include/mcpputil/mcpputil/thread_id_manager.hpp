#pragma once
#include "concurrency.hpp"
#include "declarations.hpp"
#include "singleton.hpp"
#include <gsl/gsl>
#include <mcpputil/mcpputil/boost/container/flat_map.hpp>
#include <mcpputil/mcpputil/boost/optional.hpp>
#include <thread>
#include <vector>
namespace mcpputil
{
  /**
   * \brief Class that establishes unique mapping between OS thread handles and low unique ids.
   **/
  class thread_id_manager_t : public singleton_t<thread_id_manager_t>
  {
  public:
    /**
     * \brief Id type.
     **/
    using id_type = int16_t;
    using ptr_index = int16_t;
    /**
     * \brief native handle types.
     **/
    using std_id_type = ::std::thread::id;
    thread_id_manager_t();
    thread_id_manager_t(const thread_id_manager_t &) = delete;
    thread_id_manager_t(thread_id_manager_t &&) = delete;
    thread_id_manager_t &operator=(const thread_id_manager_t &) = delete;
    thread_id_manager_t &operator=(thread_id_manager_t &&) = delete;
    /**
     * \brief Set maximum number of threads.
     *
     * Can only be called once.
     **/
    void set_max_threads(id_type max_threads) REQUIRES(!m_mutex);
    /**
     * \brief Set maximum number of TLS pointers.
     *
     * Set max threads must be called before this.
     **/
    void set_max_tls_pointers(ptr_index sz) REQUIRES(!m_mutex);
    /**
     * \brief Return maximum number of threads.
     **/
    id_type max_threads() const noexcept;
    /**
     * \brief Return max number of TLS pointers.
     **/
    auto max_tls_pointers() const noexcept -> ptr_index;
    /**
     * \brief Add current thread to manager and return id.
     **/
    id_type add_current_thread() REQUIRES(!m_mutex);
    /**
     * \brief Remove current thread.
     **/
    void remove_current_thread() REQUIRES(!m_mutex);
    /**
     * \brief Return current thread id.
     **/
    auto current_thread_id() const -> id_type;
    /**
     * \brief Return current thread id.  Does not throw.
     **/
    auto current_thread_id_noexcept() const noexcept -> ::boost::optional<id_type>;

    auto get_ptr(ptr_index i) -> void *&;
    auto get_ptr(ptr_index i) const -> void *;
    auto get_ptr_noexcept(ptr_index i) const noexcept -> ::boost::optional<void *>;
    auto set_ptr_noexcept(ptr_index i, void *) noexcept -> bool;

    auto get_ptr(id_type id, ptr_index i) -> void *&;
    auto get_ptr(id_type id, ptr_index i) const -> void *;
    auto get_ptr_noexcept(id_type id, ptr_index i) const noexcept -> ::boost::optional<void *>;
    auto set_ptr_noexcept(id_type id, ptr_index i, void *) noexcept -> bool;

  private:
    /**
     * \brief Add current thread to manager and return id.
     **/
    id_type add_thread(std_id_type) REQUIRES(!m_mutex);
    /**
     * \brief Remove thread by native handle.
     **/
    void remove_thread(std_id_type) REQUIRES(!m_mutex);
    /**
     * \brief Map of pointers for tls.
     **/
    ::std::vector<void *> m_ptr_array;
    /**
     * \brief Lock for thread id manager.
     **/
    mcpputil::mutex_t m_mutex;
    /**
     * \brief Set maximum number of tls pointers.
     **/
    ptr_index m_max_tls_pointers{0};
    /**
     * \brief Map of handles to native ids.
     **/
    ::boost::container::flat_map<std_id_type, id_type> m_native_id_map;
    /**
     * \brief Map of ids to native handles.
     **/
    ::std::vector<::boost::optional<std_id_type>> m_native_handles;
    /**
     * \brief Map of which pointers are used.
     **/
    ::std::vector<uint8_t> m_used_ptrs;
    /**
     * \brief Max number of threads.
     **/
    id_type m_max_num_threads{0};
    /**
     * \brief Fast lookup of thread id.
     **/
    static thread_local id_type t_thread_id;
  };

  inline auto thread_id_manager_t::current_thread_id() const -> id_type
  {
    if (mcpputil_unlikely(t_thread_id == ::std::numeric_limits<id_type>::max())) {
      throw ::std::runtime_error("thread_id_manager_t current_thread_id not set");
    }
    return t_thread_id;
  }
  inline auto thread_id_manager_t::current_thread_id_noexcept() const noexcept -> ::boost::optional<id_type>
  {
    if (mcpputil_unlikely(t_thread_id == ::std::numeric_limits<id_type>::max())) {
      return ::boost::none;
    }
    return t_thread_id;
  }
  inline thread_id_manager_t::id_type thread_id_manager_t::max_threads() const noexcept
  {
    return m_max_num_threads;
  }
  inline auto thread_id_manager_t::max_tls_pointers() const noexcept -> ptr_index
  {
    return m_max_tls_pointers;
  }

  inline auto thread_id_manager_t::get_ptr(ptr_index i) -> void *&
  {
    return get_ptr(current_thread_id(), i);
  }
  inline auto thread_id_manager_t::get_ptr(ptr_index i) const -> void *
  {
    return get_ptr(current_thread_id(), i);
  }
  inline auto thread_id_manager_t::get_ptr_noexcept(ptr_index i) const noexcept -> ::boost::optional<void *>
  {
    return get_ptr_noexcept(current_thread_id(), i);
  }
  inline auto thread_id_manager_t::set_ptr_noexcept(ptr_index i, void *ptr) noexcept -> bool
  {
    return set_ptr_noexcept(current_thread_id(), i, ptr);
  }
  inline auto thread_id_manager_t::get_ptr(id_type id, ptr_index i) -> void *&
  {
    return m_ptr_array.at(::gsl::narrow<size_t>(id * m_max_tls_pointers + i));
  }
  inline auto thread_id_manager_t::get_ptr(id_type id, ptr_index i) const -> void *
  {
    return m_ptr_array.at(::gsl::narrow<size_t>(id * m_max_tls_pointers + i));
  }
  inline auto thread_id_manager_t::get_ptr_noexcept(id_type id, ptr_index i) const noexcept -> ::boost::optional<void *>
  {
    if (mcpputil_unlikely(i >= m_max_tls_pointers)) {
      return ::boost::none;
    }
    auto index = id * m_max_tls_pointers + i;
    if (mcpputil_unlikely(index > ::gsl::narrow_cast<ptrdiff_t>(m_ptr_array.size()))) {
      return ::boost::none;
    }
    return m_ptr_array[::gsl::narrow<size_t>(index)];
  }
  inline auto thread_id_manager_t::set_ptr_noexcept(id_type id, ptr_index i, void *ptr) noexcept -> bool
  {
    if (mcpputil_unlikely(i >= m_max_tls_pointers)) {
      return false;
    }
    auto index = id * m_max_tls_pointers + i;
    if (mcpputil_unlikely(index > ::gsl::narrow_cast<ptrdiff_t>(m_ptr_array.size()))) {
      return false;
    }
    m_ptr_array[::gsl::narrow<size_t>(index)] = ptr;
    return true;
  }
}
