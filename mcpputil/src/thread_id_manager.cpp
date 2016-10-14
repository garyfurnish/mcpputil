#include <gsl/gsl>
#include <mcpputil/mcpputil/thread_id_manager.hpp>
namespace mcpputil
{
  thread_local thread_id_manager_t::id_type thread_id_manager_t::t_thread_id{0};
  thread_id_manager_t::thread_id_manager_t() = default;
  void thread_id_manager_t::set_max_thread(id_type max_threads)
  {
    if (m_max_num_threads)
      throw ::std::runtime_error("thread_id_manager_t max threads already set");
    m_max_num_threads = max_threads;
    m_native_handles.resize(m_max_num_threads);
  }
  auto thread_id_manager_t::add_current_thread() -> id_type
  {
    t_thread_id = add_thread(::std::this_thread::get_id());
    return t_thread_id;
  }
  auto thread_id_manager_t::add_thread(std_id_type sid) -> id_type
  {
    auto it = m_native_id_map.find(sid);
    if (it != m_native_id_map.end())
      return it->second;
    auto avail_id_it = ::std::find(m_native_handles.begin(), m_native_handles.end(), ::boost::none);
    if (avail_id_it == m_native_handles.end())
      throw ::std::runtime_error("thread_id_manager_t out of handles.");
    auto new_id = ::gsl::narrow<id_type>(avail_id_it - m_native_handles.begin());
    *avail_id_it = sid;
    m_native_id_map[sid] = new_id;
    return new_id;
  }
  void thread_id_manager_t::remove_thread(std_id_type sid)
  {
    auto it = m_native_id_map.find(sid);
    if (it == m_native_id_map.end())
      return;
    auto id = it->second;
    m_native_handles.at(id) = ::boost::none;
    m_native_id_map.erase(it);
  }
  void thread_id_manager_t::remove_current_thread()
  {
    remove_thread(::std::this_thread::get_id());
    t_thread_id = 0;
  }
}
