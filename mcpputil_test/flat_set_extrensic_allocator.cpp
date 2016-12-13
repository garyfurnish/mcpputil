#include <algorithm>
#include <mcpputil/mcpputil/bandit.hpp>
#include <mcpputil/mcpputil/flat_set_extrensic_allocator.hpp>
#include <memory>
using namespace bandit;

void test_flat_set_extrensic_allocator()
{
  using mcpputil::flat_set_extrensic_allocator_t;
  describe("flat_set_extrensic_allocator", []() {
    it("constructor 268a6445-5988-4357-87d2-294564dc07e1", []() {
      flat_set_extrensic_allocator_t<int> set;
      ::std::allocator<int> alloc;
      int a = 5;
      int b = 3;
      int c = 7;
      set.insert(a, alloc);
      set.insert(b, alloc);
      set.insert(c, alloc);
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
  });
}
