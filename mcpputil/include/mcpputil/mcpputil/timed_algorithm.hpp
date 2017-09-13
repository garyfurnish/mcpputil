#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>

namespace mcpputil
{
  /**
   * \brief Timed for_each algorithm.
   * @return Elapsed time using high resolution clock.
   **/
  template <typename Container, typename F>
  [[nodiscard]] auto timed_for_each(Container &&container, F &&f)
  {
    ::std::chrono::high_resolution_clock::time_point t1, t2;
    t1 = ::std::chrono::high_resolution_clock::now();
    ::std::for_each(::std::begin(container), ::std::end(container), f);
    t2 = ::std::chrono::high_resolution_clock::now();
    return ::std::chrono::duration_cast<::std::chrono::duration<double>>(t2 - t1);
  }
  /**
   * \brief Timed invoke algorithm.
   * @return tuple of return value and elapsed time using high resolution clock.
   **/
  template <typename F, typename... Args, ::std::enable_if_t<!::std::is_void<::std::result_of_t<F(Args...)>>::value, int> = 0>
  [[nodiscard]] auto timed_invoke(F &&f, Args... args)
  {
    ::std::chrono::high_resolution_clock::time_point t1, t2;
    t1 = ::std::chrono::high_resolution_clock::now();
    auto ret = ::std::invoke(::std::forward<F>(f), ::std::forward<Args>(args)...);
    t2 = ::std::chrono::high_resolution_clock::now();
    return ::std::make_tuple(::std::move(ret), ::std::chrono::duration_cast<::std::chrono::duration<double>>(t2 - t1));
  }
  /**
   * \brief Timed invoke algorithm.
   * @return Elapsed time using high resolution clock in a tuple.
   **/
  template <typename F, typename... Args, ::std::enable_if_t<::std::is_void<::std::result_of_t<F(Args...)>>::value, int> = 0>
  [[nodiscard]] auto timed_invoke(F &&f, Args... args)
  {
    ::std::chrono::high_resolution_clock::time_point t1, t2;
    t1 = ::std::chrono::high_resolution_clock::now();
    ::std::invoke(::std::forward<F>(f), ::std::forward<Args>(args)...);
    t2 = ::std::chrono::high_resolution_clock::now();
    return ::std::make_tuple(::std::chrono::duration_cast<::std::chrono::duration<double>>(t2 - t1));
  }
} // namespace mcpputil
