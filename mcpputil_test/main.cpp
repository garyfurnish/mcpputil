#include <mcpputil/mcpputil/backed_ordered_map.hpp>
#include <mcpputil/mcpputil/bandit.hpp>
#include <mcpputil/mcpputil/intrinsics.hpp>
#include <mcpputil/mcpputil/literals.hpp>
#include <mcpputil/mcpputil/thread_id_manager.hpp>
void test_vector_extrensic_allocator();
void test_flat_set_extrensic_allocator();
using namespace bandit;
using namespace snowhouse;
using namespace ::mcpputil::literals;
template class ::mcpputil::containers::backed_ordered_multimap<int, int, ::std::less<int>>;
go_bandit([]() {
  describe("thread_id_manager", []() {
    it("manager setup", []() {
      auto manager = ::std::make_unique<mcpputil::thread_id_manager_t>();
      manager->set_max_threads(100);
      AssertThat(manager->max_threads(), Equals(100));
      manager->set_max_tls_pointers(10);
      AssertThat(manager->max_tls_pointers(), Equals(10));
      manager.release();
    });
    it("manager test", []() {
      AssertThat(mcpputil::thread_id_manager_t::gs().add_current_thread(), Equals(0));
      AssertThat(mcpputil::thread_id_manager_t::gs().add_current_thread(), Equals(0));
      mcpputil::thread_id_manager_t::gs().remove_current_thread();
      AssertThat(mcpputil::thread_id_manager_t::gs().add_current_thread(), Equals(0));
      AssertThat(mcpputil::thread_id_manager_t::gs().add_current_thread(), Equals(0));
      ::std::atomic<bool> success{false};
      auto test_thread = [&success]() {
        if (mcpputil::thread_id_manager_t::gs().add_current_thread() != 1) {
          return;
        }
        if (mcpputil::thread_id_manager_t::gs().add_current_thread() != 1) {
          return;
        }
        mcpputil::thread_id_manager_t::gs().remove_current_thread();
        if (mcpputil::thread_id_manager_t::gs().add_current_thread() != 1) {
          return;
        }
        if (mcpputil::thread_id_manager_t::gs().add_current_thread() != 1) {
          return;
        }
        success = true;
      };
      ::std::thread(test_thread).join();
      AssertThat(static_cast<bool>(success), IsTrue());
    });
  });
  describe("intrinsics", []() {
    it("popcount", []() {
      AssertThat(::mcpputil::popcount(0_sz), Equals(0_sz));
      AssertThat(::mcpputil::popcount(5_sz), Equals(2_sz));
    });
    it("ffs", []() {
      AssertThat(::mcpputil::ffs(0_sz), Equals(0_sz));
      AssertThat(::mcpputil::ffs(1_sz), Equals(1_sz));
      AssertThat(::mcpputil::ffs(8_sz), Equals(4_sz));
      AssertThat(::mcpputil::ffs(10_sz), Equals(2_sz));
    });
    it("clz", []() {
      AssertThat(::mcpputil::clz(1_sz), Equals(63_sz));
      AssertThat(::mcpputil::clz(8_sz), Equals(60_sz));
      AssertThat(::mcpputil::clz(10_sz), Equals(60_sz));
      AssertThat(::mcpputil::clz(::std::numeric_limits<size_t>::max()), Equals(0_sz));
    });
  });
  describe("backed_ordered_multimap", []() {
    using bom_t = ::mcpputil::containers::backed_ordered_multimap<size_t, size_t>;
    it("backed_ordered_multimap_test0", []() {
      size_t array[500];
      bom_t map(array, sizeof(array));
      AssertThat(map.size(), Equals(0_sz));
      auto ret = map.insert(::std::make_pair(5, 0));
      AssertThat(map.size(), Equals(1_sz));
      AssertThat(ret.first, Equals(map.begin()));
      AssertThat(ret.second, IsTrue());
      ret = map.insert(::std::make_pair(4, 1));

      AssertThat(map.size(), Equals(2_sz));
      AssertThat(ret.first, Equals(map.begin()));
      AssertThat(ret.second, IsTrue());
      ret = map.insert(::std::make_pair(3, 2));

      AssertThat(map.size(), Equals(3_sz));
      AssertThat(ret.first, Equals(map.begin()));
      AssertThat(ret.second, IsTrue());
      ret = map.insert(::std::make_pair(2, 3));
      AssertThat(map.size(), Equals(4_sz));
      AssertThat(ret.first, Equals(map.begin()));
      AssertThat(ret.second, IsTrue());
      ret = map.insert(::std::make_pair(1, 2));

      AssertThat(map.size(), Equals(5_sz));
      AssertThat(ret.first, Equals(map.begin()));
      AssertThat(ret.second, IsTrue());
      ret = map.insert(::std::make_pair(0, 1));

      AssertThat(map.size(), Equals(6_sz));
      AssertThat(ret.first, Equals(map.begin()));
      AssertThat(ret.second, IsTrue());
      AssertThat(map.find(3_sz), Equals(map.begin() + 3));
      AssertThat(map.find(88_sz), Equals(map.end()));
      AssertThat(map.erase(3_sz), Equals(1_sz));
      AssertThat(map.find(3_sz), Equals(map.end()));

      ret = map.insert(::std::make_pair(3, 2));
      AssertThat(ret.first, Equals(map.begin() + 3));
      AssertThat(ret.second, IsTrue());
      ::std::vector<::std::pair<size_t, size_t>> t1{{0, 1}, {1, 2}, {2, 3}, {3, 2}, {4, 1}, {5, 0}};
      AssertThat(::std::equal(map.begin(), map.end(), t1.begin()), IsTrue());
      map.move(0_sz, {4, 3});
      ::std::vector<::std::pair<size_t, size_t>> t2{{1, 2}, {2, 3}, {3, 2}, {4, 1}, {4, 3}, {5, 0}};
      AssertThat(::std::equal(map.begin(), map.end(), t2.begin()), IsTrue());
      map.move(3_sz, {0, 50});
      ::std::vector<::std::pair<size_t, size_t>> t3{{0, 50}, {1, 2}, {2, 3}, {4, 1}, {4, 3}, {5, 0}};
      AssertThat(::std::equal(map.begin(), map.end(), t3.begin()), IsTrue());
      map.move(0_sz, {0, 51});
      ::std::vector<::std::pair<size_t, size_t>> t4{{0, 51}, {1, 2}, {2, 3}, {4, 1}, {4, 3}, {5, 0}};
      AssertThat(::std::equal(map.begin(), map.end(), t4.begin()), IsTrue());
      /*      for (auto &&obj : map) {
        ::std::cout << "(" << obj.first << "," << obj.second << ")";
      }
      ::std::cout << "\n";*/
    });
    it("backed_ordered_multimap_test1", []() {
      uint8_t array[31];
      bom_t map(array, sizeof(array));
      AssertThat(map.capacity(), Equals(1_sz));
      auto ret = map.insert(::std::make_pair(5, 0));
      AssertThat(map.size(), Equals(1_sz));
      AssertThat(ret.second, IsTrue());
      ret = map.insert(::std::make_pair(5, 1));
      AssertThat(map.size(), Equals(1_sz));
      AssertThat(ret.second, IsFalse());
      ::std::vector<::std::pair<size_t, size_t>> t1{{5, 0}, {5, 1}};
      AssertThat(::std::equal(map.begin(), map.end(), t1.begin()), IsTrue());

    });
    it("backed_ordered_multimap_test1", []() {
      size_t array[500];
      bom_t map(array, sizeof(array));
      auto ret = map.insert(::std::make_pair(5, 0));
      ret = map.insert(::std::make_pair(5, 1));
      ::std::vector<::std::pair<size_t, size_t>> t1{{5, 0}, {5, 1}};
      AssertThat(::std::equal(map.begin(), map.end(), t1.begin()), IsTrue());
    });
    it("backed_ordered_multimap_test2", []() {
      size_t array[500];
      bom_t map(array, sizeof(array));
      map.insert(::std::make_pair(0, 5));
      AssertThat(map.lower_bound(0), Equals(map.begin()));
      AssertThat(map.find(0), Equals(map.begin()));

    });

  });
  test_vector_extrensic_allocator();
  test_flat_set_extrensic_allocator();
});

int main(int argc, char *argv[])
{
  auto ret = bandit::run(argc, argv);
#ifdef _WIN32
  ::std::cin.get();
#endif
  return ret;
}
