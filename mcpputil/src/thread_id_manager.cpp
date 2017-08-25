#include <gsl/gsl>
#include <mcpputil/mcpputil/thread_id_manager.hpp>
namespace mcpputil
{
	MCPPUTIL_DLL_PUBLIC thread_id_manager_t& get_thread_id_manager()
	{
		static thread_id_manager_t tim{};
		return tim;
	}
#ifdef _WINDLL
	thread_local thread_id_manager_t::id_type t_thread_id{ ::std::numeric_limits<thread_id_manager_t::id_type>::max() };
	auto thread_id_manager_t::current_thread_id() const -> id_type
	{
		if (mcpputil_unlikely(t_thread_id == ::std::numeric_limits<id_type>::max())) {
			throw ::std::runtime_error("thread_id_manager_t current_thread_id not set");
		}
		return t_thread_id;
	}
	auto thread_id_manager_t::current_thread_id_noexcept() const noexcept -> ::boost::optional<id_type>
	{
		if (mcpputil_unlikely(t_thread_id == ::std::numeric_limits<id_type>::max())) {
			return ::boost::none;
		}
		return t_thread_id;
	}
#else
	thread_local thread_id_manager_t::id_type thread_id_manager_t::t_thread_id{
		::std::numeric_limits<thread_id_manager_t::id_type>::max() };
#endif
  thread_id_manager_t::thread_id_manager_t() = default;
  void thread_id_manager_t::set_max_tls_pointers(ptr_index sz)
  {
    MCPPALLOC_CONCURRENCY_LOCK_GUARD(m_mutex);
    if (m_max_tls_pointers != 0) {
      throw ::std::runtime_error("thread_id_manager_t max tls pointers already set.");
    }
    if (m_max_num_threads == 0) {
      throw ::std::runtime_error("thread_id_manager_t max num threads must be set before setting max tls pointers.");
    }
    m_max_tls_pointers = sz;
    m_ptr_array.resize(::gsl::narrow<size_t>(m_max_num_threads * m_max_tls_pointers));
    for (auto &&obj : m_ptr_array) {
      obj = nullptr;
    }
  }
  void thread_id_manager_t::set_max_threads(id_type max_threads)
  {
    MCPPALLOC_CONCURRENCY_LOCK_GUARD(m_mutex);
    if (m_max_num_threads != 0) {
      throw ::std::runtime_error("thread_id_manager_t max threads already set");
    }
    m_max_num_threads = max_threads;
    m_native_handles.resize(::gsl::narrow<size_t>(m_max_num_threads));
  }
  auto thread_id_manager_t::add_current_thread() -> id_type
  {
    t_thread_id = add_thread(::std::this_thread::get_id());
    return t_thread_id;
  }
  auto thread_id_manager_t::add_thread(std_id_type sid) -> id_type
  {
    MCPPALLOC_CONCURRENCY_LOCK_GUARD(m_mutex);
    auto it = m_native_id_map.find(sid);
    if (it != m_native_id_map.end()) {
      return it->second;
    }
    auto avail_id_it = ::std::find(m_native_handles.begin(), m_native_handles.end(), ::boost::none);
    if (avail_id_it == m_native_handles.end()) {
      throw ::std::runtime_error("thread_id_manager_t out of handles.");
    }
    auto new_id = ::gsl::narrow<id_type>(avail_id_it - m_native_handles.begin());
    *avail_id_it = sid;
    m_native_id_map[sid] = new_id;
    return new_id;
  }
  void thread_id_manager_t::remove_thread(std_id_type sid)
  {
    MCPPALLOC_CONCURRENCY_LOCK_GUARD(m_mutex);
    auto it = m_native_id_map.find(sid);
    if (it == m_native_id_map.end()) {
      return;
    }
    auto id = it->second;
    m_native_handles.at(::gsl::narrow<size_t>(id)) = ::boost::none;
    m_native_id_map.erase(it);
  }
  void thread_id_manager_t::remove_current_thread()
  {
    remove_thread(::std::this_thread::get_id());
    t_thread_id = 0;
  }
} // namespace mcpputil
