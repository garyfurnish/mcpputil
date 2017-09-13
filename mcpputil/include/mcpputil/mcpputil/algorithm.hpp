
namespace mcpputil
{
  /**
   * \brief for_each algorithm starting from the back.
   *
   * This algorithm is safe for insertion and deletion.
   **/
  template <typename Container, typename F>
  void reverse_consume_for_each(Container &&c, F &&f)
  {
    while (!c.empty()) {
      const auto it = c.rbegin();
      c.erase((it + 1).base());
      const auto val = *it;
      f(val);
    }
  }
} // namespace mcpputil
