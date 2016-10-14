#pragma once
#include "declarations.hpp"
#include <boost/optional.hpp>
#include <mcpputil/mcpputil/boost/container/flat_map.hpp>
#include <thread>
#include <vector>
namespace mcpputil
{
  /**
   * \brief Class that establishes unique mapping between OS thread handles and low unique ids.
   **/
  class thread_id_manager_t
  {
  public:
    /**
     * \brief Id type.
     **/
    using id_type = uint16_t;
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
    void set_max_thread(id_type max_threads);
    /**
     * \brief Add current thread to manager and return id.
     **/
    auto add_current_thread() -> id_type;
    /**
     * \brief Remove current thread.
     **/
    void remove_current_thread();
    /**
     * \brief Return current thread id.
     **/
    auto current_thread_id() const -> id_type;
    /**
     * \brief Return current thread id.  Does not throw.
     **/
    auto current_thread_id_noexcept() const noexcept -> ::boost::optional<id_type>;

  private:
    /**
     * \brief Add current thread to manager and return id.
     **/
    auto add_thread(std_id_type) -> id_type;
    /**
     * \brief Remove thread by native handle.
     **/
    void remove_thread(std_id_type);
    /**
     * \brief Map of handles to native ids.
     **/
    ::boost::container::flat_map<std_id_type, id_type> m_native_id_map;
    /**
     * \brief Map of ids to native handles.
     **/
    ::std::vector<::boost::optional<std_id_type>> m_native_handles;
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
    if (mcpputil_unlikely(t_thread_id == 0))
      throw ::std::runtime_error("thread_id_manager_t current_thread_id not set");
    return t_thread_id;
  }
  inline auto thread_id_manager_t::current_thread_id_noexcept() const noexcept -> ::boost::optional<id_type>
  {
    if (mcpputil_unlikely(t_thread_id == 0))
      return ::boost::none;
    return t_thread_id;
  }
}
