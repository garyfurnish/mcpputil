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
    it("insert da003908-0e0d-4c6c-9493-2fdee9480b8e", []() {
      // std::pair<iterator, bool> insert(const value_type &value, Allocator &allocator);
      // test adding to empty set
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set;
      int i = 3;
      set.insert(i, alloc);
      ::std::array<int, 1> array{{i}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert 21412e06-df25-4eee-8a26-e7b333ec9a16", []() {
      // std::pair<iterator, bool> insert(const value_type &value, Allocator &allocator);
      // test to make sure can't add duplicates.
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      int i = 3;
      auto ret = set.insert(i, alloc);
      AssertThat(ret.second, IsFalse());
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert 8628718a-c4dd-463c-a38a-55798e509fac", []() {
      // std::pair<iterator, bool> insert(value_type &&value, Allocator &allocator);
      // test adding to empty set
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set;
      set.insert(3, alloc);
      ::std::array<int, 1> array{{3}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert 8628718a-c4dd-463c-a38a-55798e509fac", []() {
      // std::pair<iterator, bool> insert(value_type &&value, Allocator &allocator);
      // test to make sure can't add duplicates.
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      auto ret = set.insert(3, alloc);
      AssertThat(ret.second, IsFalse());
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert_search df30b3ac-1ae9-4244-a3c4-4536f78cf7bf", []() {
      //    iterator insert(const_iterator hint, const value_type &value, Allocator &allocator);
      // test invalid hint
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      int i = 4;
      set.insert_search(set.begin() + 2, i, alloc);
      AssertThat(set.size(), Equals(4));
      ::std::array<int, 4> array{{3, 5, 4, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert_search 9a518d8c-2dad-4f19-bb33-792b55afe57b", []() {
      //    iterator insert_search(const_iterator hint, const value_type &value, Allocator &allocator);
      // test valid hint
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      int i = 6;
      set.insert_search(set.begin() + 1, i, alloc);
      AssertThat(set.size(), Equals(4));
      ::std::array<int, 4> array{{3, 5, 6, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert_search 6b649432-c3f5-4036-b852-8ba4e9110fe3", []() {
      //    iterator insert_search(const_iterator hint, const value_type &value, Allocator &allocator);
      // test adding to empty set
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set;
      int i = 6;
      set.insert_search(set.begin(), i, alloc);
      AssertThat(set.size(), Equals(1));
      ::std::array<int, 1> array{{6}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert_search 4e250601-f6de-4ae9-b473-f2a6641d44ab", []() {
      //    iterator insert_search(const_iterator hint, const value_type &value, Allocator &allocator);
      // test to make sure can't add duplicates
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      int i = 5;
      auto ret = set.insert_search(set.begin() + 1, i, alloc);
      AssertThat(ret.second, Equals(false));
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert 3c4c937f-f16d-490f-94b0-0e1cab63359a", []() {
      //    iterator insert_search(const_iterator hint, value_type &&value, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert 8093d8fb-c70d-401a-9d1c-c761cce75b59", []() {
      //    void insert(InputIt first, InputIt last, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert 4bef14f0-4c22-444f-9000-e957a8da3896", []() {
      //    void insert(std::initializer_list<value_type> ilist, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("inset_sorted_contiguous 95428789-67b9-4477-a155-e99a48db9d3f", []() {
      //    void insert_sorted_contiguous(InputIt first, InputIt last, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("erase 72f4d92f-cdad-421e-92c9-4c8219896a85", []() {
      //    size_t erase(const key_type &key, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("find 5e983de9-c2f0-4adb-b97e-6737c5968682", []() {
      //    const_iterator find(const key_type &key) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("find 0a8f6baa-ef3d-4d8b-bb6a-cc65934f55ff", []() {
      //    iterator find(const FK &x);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("find 9f306801-6e6b-419e-895b-b07dc48d1a55", []() {
      //    const_iterator find(const FK &x) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("lower_bound 7e34cc2c-f859-486d-b102-332b736d30f7", []() {
      //    iterator lower_bound(const key_type &key);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("lower_bound 7e5403ef-6bec-44ab-9914-374cf95d97ed", []() {
      //    const_iterator lower_bound(const key_type &key) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("lower_bound 834bafb8-f287-4630-b51e-3f5dd1dd83da", []() {
      //    iterator lower_bound(const FK &x);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("lower_bound 78ed0aeb-872a-4d1f-a045-32ecdcb163bf", []() {
      //    const_iterator lower_bound(const FK &x) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("upper_bound 9b11c5a6-6d7a-4899-8488-d6366cacc822", []() {
      //    const_iterator lower_bound(const FK &x) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("upper_bound 04600d0b-aa17-4890-800f-13a42d6a135f", []() {
      //    iterator upper_bound(const key_type &key);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("upper_bound f3bf8d59-bdd1-4d43-ab9e-53214f4eb3a0", []() {
      //    const_iterator upper_bound(const key_type &key) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("upper_bound 6825b9b9-62ea-4306-be15-edd96ca20244", []() {
      //    iterator upper_bound(const FK &x);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("upper_bound 769a5c52-4d00-4105-b272-0e055fd534ae", []() {
      //    const_iterator upper_bound(const FK &x) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

  });
}
