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
      //    flat_set_extrensic_allocator_t();
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
    it("constructor 388294c9-37d4-4788-b564-23b94cb73b3f", []() {
      //    explicit flat_set_extrensic_allocator_t(const Compare &comp);
      flat_set_extrensic_allocator_t<int> set{::std::less<>{}};
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
    it("constructor c3bf8c4d-9c33-4e3d-80d2-17e8935cd197 ", []() {
      /*
  flat_set_extrensic_allocator_t(InputIt first,
                                 InputIt last,
                                 Allocator &alloc,
                                 const compare_type &comp = compare_type{});
      */
      ::std::allocator<int> alloc;
      ::std::array<int, 3> array{{3, 5, 7}};
      flat_set_extrensic_allocator_t<int> set{array.begin(), array.end(), alloc};
      AssertThat(set.size(), Equals(3));
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("constructor 02989d63-9bf2-4c54-8bd3-f2319c3f5c1e", []() {
      //    flat_set_extrensic_allocator_t(flat_set_extrensic_allocator_t &&other);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      flat_set_extrensic_allocator_t<int> set2{::std::move(set)};
      AssertThat(set.size(), Equals(0));
      AssertThat(set2.size(), Equals(3));
      AssertThat(set.capacity(), Equals(0));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set2.begin(), set2.end(), array.begin()), IsTrue());
      set.destroy(alloc);
      set2.destroy(alloc);

    });
    it("constructor ee50dd07-6f66-45e9-b73c-66c87fcf5468", []() {
      //    flat_set_extrensic_allocator_t(flat_set_extrensic_allocator_t &&other);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      flat_set_extrensic_allocator_t<int> set2{::std::move(set)};
      AssertThat(set.size(), Equals(0));
      AssertThat(set2.size(), Equals(3));
      AssertThat(set.capacity(), Equals(0));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set2.begin(), set2.end(), array.begin()), IsTrue());
      set.destroy(alloc);
      set2.destroy(alloc);
    });
    it("constructor cdadce2d-01b4-4d01-a554-8fb85cfc0760", []() {
      /*
  flat_set_extrensic_allocator_t(std::initializer_list<value_type> init,
                                 Allocator &alloc,
                                 const compare_type &comp = compare_type{});
      */
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

  });
}
