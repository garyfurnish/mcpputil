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

    it("insert_search 599e97e2-69a9-476c-986c-db969a77d1ba", []() {
      //    iterator insert(const_iterator hint, value_type&&, Allocator &allocator);
      // test invalid hint
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      set.insert_search(set.begin() + 2, 4, alloc);
      AssertThat(set.size(), Equals(4));
      ::std::array<int, 4> array{{3, 5, 4, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert_search 962a6c15-d76a-461d-ae6c-c8d4cc592b31", []() {
      //    iterator insert_search(const_iterator hint, value_type&&, Allocator &allocator);
      // test valid hint
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      set.insert_search(set.begin() + 1, 6, alloc);
      AssertThat(set.size(), Equals(4));
      ::std::array<int, 4> array{{3, 5, 6, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert_search d8d60193-efe2-4719-98d3-8735ac0ba4a4", []() {
      //    iterator insert_search(const_iterator hint, value_type&&, Allocator &allocator);
      // test adding to empty set
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set;
      set.insert_search(set.begin(), 6, alloc);
      AssertThat(set.size(), Equals(1));
      ::std::array<int, 1> array{{6}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert_search 1cf3ee5d-5411-46bf-a021-9283eb9b1cdd", []() {
      //    iterator insert_search(const_iterator hint, value_type&&, Allocator &allocator);
      // test to make sure can't add duplicates
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      auto ret = set.insert_search(set.begin() + 1, 5, alloc);
      AssertThat(ret.second, Equals(false));
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert e2b4ca85-0313-4fcb-9b9d-f175d77df462", []() {
      //    iterator insert(const_iterator hint, const value_type &value, Allocator &allocator);
      // test invalid hint
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      int i = 4;
      set.insert(set.begin() + 2, i, alloc);
      AssertThat(set.size(), Equals(4));
      ::std::array<int, 4> array{{3, 4, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert 3e56bc69-5f24-4149-a914-cf3c7bf8bd61", []() {
      //    iterator insert(const_iterator hint, const value_type &value, Allocator &allocator);
      // test valid hint
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      int i = 6;
      set.insert(set.begin() + 1, i, alloc);
      AssertThat(set.size(), Equals(4));
      ::std::array<int, 4> array{{3, 5, 6, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert 0a333720-cc93-48cc-8fed-16a112476e41", []() {
      //    iterator insert(const_iterator hint, const value_type &value, Allocator &allocator);
      // test adding to empty set
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set;
      int i = 6;
      set.insert(set.begin(), i, alloc);
      AssertThat(set.size(), Equals(1));
      ::std::array<int, 1> array{{6}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert 28b3f378-68f1-4bfa-afd4-697bdae08d68", []() {
      //    iterator insert(const_iterator hint, const value_type &value, Allocator &allocator);
      // test to make sure can't add duplicates
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      int i = 5;
      auto ret = set.insert(set.begin() + 1, i, alloc);
      AssertThat(ret.second, Equals(false));
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert 599e97e2-69a9-476c-986c-db969a77d1ba", []() {
      //    iterator insert(const_iterator hint, value_type&&, Allocator &allocator);
      // test invalid hint
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      set.insert(set.begin() + 2, 4, alloc);
      AssertThat(set.size(), Equals(4));
      ::std::array<int, 4> array{{3, 4, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert 4c9ee0ae-ab00-4027-91ae-3c644c45a217", []() {
      //    iterator insert(const_iterator hint, value_type&&, Allocator &allocator);
      // test valid hint
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      set.insert(set.begin() + 1, 6, alloc);
      AssertThat(set.size(), Equals(4));
      ::std::array<int, 4> array{{3, 5, 6, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert 06fb993c-6bad-47f1-9238-aed5e2cb4803", []() {
      //    iterator insert(const_iterator hint, value_type&&, Allocator &allocator);
      // test adding to empty set
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set;
      set.insert(set.begin(), 6, alloc);
      AssertThat(set.size(), Equals(1));
      ::std::array<int, 1> array{{6}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert c482dd80-c7d6-4a55-9142-ef40ce5cb2e9", []() {
      //    iterator insert(const_iterator hint, value_type&&, Allocator &allocator);
      // test to make sure can't add duplicates
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      auto ret = set.insert(set.begin() + 1, 5, alloc);
      AssertThat(ret.second, Equals(false));
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 3> array{{3, 5, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });

    it("insert 8093d8fb-c70d-401a-9d1c-c761cce75b59", []() {
      //    void insert(InputIt first, InputIt last, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      ::std::array<int, 4> ia{{6, 7, 8, 9}};
      set.insert(ia.begin(), ia.end(), alloc);
      AssertThat(set.size(), Equals(6));
      ::std::array<int, 6> array{{3, 5, 6, 7, 8, 9}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("insert 4bef14f0-4c22-444f-9000-e957a8da3896", []() {
      //    void insert(std::initializer_list<value_type> ilist, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      set.insert({6, 7, 8, 9}, alloc);
      AssertThat(set.size(), Equals(6));
      ::std::array<int, 6> array{{3, 5, 6, 7, 8, 9}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("inset_sorted_contiguous 95428789-67b9-4477-a155-e99a48db9d3f", []() {
      //    void insert_sorted_contiguous(InputIt first, InputIt last, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      ::std::array<int, 3> ia{{7, 8, 9}};
      set.insert_sorted_contiguous(ia.begin(), ia.end(), alloc);
      AssertThat(set.size(), Equals(3));
      ::std::array<int, 6> array{{3, 5, 7, 8, 9, 75}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("erase 72f4d92f-cdad-421e-92c9-4c8219896a85", []() {
      //    size_t erase(const key_type &key, Allocator &allocator);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      set.erase(5, alloc);
      AssertThat(set.size(), Equals(2));
      ::std::array<int, 2> array{{3, 7}};
      AssertThat(::std::equal(set.begin(), set.end(), array.begin()), IsTrue());
      set.destroy(alloc);
    });
    it("find 404c9ce1-91d6-4ba1-861c-03a7e565a561", []() {
      //    iterator find(const key_type &key) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.find(3), Equals(set.begin()));
      AssertThat(set.find(5), Equals(set.begin() + 1));
      AssertThat(set.find(7), Equals(set.begin() + 2));
      AssertThat(set.find(8), Equals(set.end()));
      set.destroy(alloc);
    });
    it("find 5e983de9-c2f0-4adb-b97e-6737c5968682", []() {
      //    const_iterator find(const key_type &key) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      const auto &cset = set;
      AssertThat(cset.find(3), Equals(set.begin()));
      AssertThat(cset.find(5), Equals(set.begin() + 1));
      AssertThat(cset.find(7), Equals(set.begin() + 2));
      AssertThat(cset.find(8), Equals(set.end()));
      set.destroy(alloc);
    });
    it("find 0a8f6baa-ef3d-4d8b-bb6a-cc65934f55ff", []() {
      //    iterator find(const FK &x);
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      AssertThat(set.find(3l), Equals(set.begin()));
      AssertThat(set.find(5l), Equals(set.begin() + 1));
      AssertThat(set.find(7l), Equals(set.begin() + 2));
      AssertThat(set.find(8l), Equals(set.end()));
      set.destroy(alloc);
    });
    it("find 9f306801-6e6b-419e-895b-b07dc48d1a55", []() {
      //    const_iterator find(const FK &x) const;
      ::std::allocator<int> alloc;
      flat_set_extrensic_allocator_t<int> set{{3, 5, 7}, alloc};
      const auto &cset = set;
      AssertThat(cset.find(3l), Equals(set.begin()));
      AssertThat(cset.find(5l), Equals(set.begin() + 1));
      AssertThat(cset.find(7l), Equals(set.begin() + 2));
      AssertThat(cset.find(8l), Equals(set.end()));
      set.destroy(alloc);
    });
  });
}
