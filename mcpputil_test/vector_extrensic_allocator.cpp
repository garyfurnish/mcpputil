#include <algorithm>
#include <mcpputil/mcpputil/bandit.hpp>
#include <mcpputil/mcpputil/vector_extrensic_allocator.hpp>
#include <memory>
using namespace bandit;

void test_vector_extrensic_allocator()
{
  using mcpputil::vector_extrensic_allocator_t;
  describe("vector_extrensic_allocator", []() {
    it("constructor 59be4c4b-71a6-4ef7-8f5c-0367cb8e7109", []() {
      auto v = vector_extrensic_allocator_t<int>();
      AssertThat(v.size(), Equals(0));
      AssertThat(v.capacity(), Equals(0));
    });
    it("constructor e88a468a-40fd-4b39-aee8-97b40ec31eac", []() {
      auto alloc = ::std::allocator<int>();
      auto v = vector_extrensic_allocator_t<int>(5, alloc);
      AssertThat(v.size(), Equals(5));
      AssertThat(v.capacity(), IsGreaterThanOrEqualTo(5));
      v.destroy(alloc);
    });
    it("constructor db4d9ee7-c2f1-4e28-aad3-107e3a021b98", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      AssertThat(v.size(), Equals(5));
      AssertThat(v.capacity(), IsGreaterThanOrEqualTo(5));
      AssertThat(::std::equal(v.begin(), v.end(), a.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("constructor 918beb77-546f-4544-a15c-f8a563d67103", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>({1, 2, 3, 4, 5}, alloc);
      AssertThat(v.size(), Equals(5));
      AssertThat(v.capacity(), IsGreaterThanOrEqualTo(5));
      AssertThat(::std::equal(v.begin(), v.end(), a.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("constructor fdeace50-3e61-42c1-bb17-99e62641fa60", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      vector_extrensic_allocator_t<int> v2(v, alloc);
      AssertThat(v.size(), Equals(5));
      AssertThat(v.capacity(), IsGreaterThanOrEqualTo(5));
      AssertThat(::std::equal(v.begin(), v.end(), a.begin()), IsTrue());
      AssertThat(v2.size(), Equals(5));
      AssertThat(v2.capacity(), IsGreaterThanOrEqualTo(5));
      AssertThat(::std::equal(v2.begin(), v2.end(), a.begin()), IsTrue());
      v.destroy(alloc);
      v2.destroy(alloc);
    });
    it("constructor b039c548-a8d5-47c7-be35-73cf7689fa51", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      vector_extrensic_allocator_t<int> v2{::std::move(v)};
      AssertThat(v.data() == nullptr, IsTrue());
      AssertThat(v.size(), Equals(0));
      AssertThat(v.capacity(), Equals(0));
      AssertThat(v2.size(), Equals(5));
      AssertThat(v2.capacity(), IsGreaterThanOrEqualTo(5));
      AssertThat(::std::equal(v2.begin(), v2.end(), a.begin()), IsTrue());
      v.destroy(alloc);
      v2.destroy(alloc);
    });
    it("assign db4d9ee7-c2f1-4e28-aad3-107e3a021b98", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.assign(6, 6, alloc);
      ::std::array<int, 6> b{{6, 6, 6, 6, 6, 6}};
      AssertThat(v.size(), Equals(6));
      AssertThat(v.capacity(), IsGreaterThanOrEqualTo(6));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("reverse iterator 2c0f709f-0e12-4d6d-ad16-db1a8188bb7e", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      AssertThat(*(v.rend() - 1), Equals(1));
      AssertThat(*v.rbegin(), Equals(5));
      v.destroy(alloc);
    });
    it("insert 5336be58-122c-47b8-a557-5c73629025de", []() {
      //    iterator insert(const_iterator pos, const T &value, Allocator &allocator);
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      ::std::array<int, 6> b{{1, 2, 6, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      int i = 6;
      v.insert(v.begin() + 2, i, alloc);
      AssertThat(v.size(), Equals(6));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("insert 48ec2d6b-28ab-42e5-b54f-7d46002de612", []() {
      //    iterator insert(const_iterator pos, T &&value, Allocator &allocator);
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      ::std::array<int, 6> b{{1, 2, 6, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.insert(v.begin() + 2, 6, alloc);
      AssertThat(v.size(), Equals(6));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("insert 48ec2d6b-28ab-42e5-b54f-7d46002de612", []() {
      //    iterator insert(const_iterator pos, index_type count, const T &value, Allocator &allocator);
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      ::std::array<int, 7> b{{1, 2, 6, 6, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.insert(v.begin() + 2, 2, 6, alloc);
      AssertThat(v.size(), Equals(7));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });

    it("insert 4ad86ffe-93df-4493-b228-efa6c43c18d3", []() {
      //    iterator insert(const_iterator pos, InputIt first, InputIt last, Allocator &allocator)
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      ::std::array<int, 7> b{{1, 2, 6, 7, 3, 4, 5}};
      ::std::array<int, 2> c{{6, 7}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.insert(v.begin() + 2, c.begin(), c.end(), alloc);
      AssertThat(v.size(), Equals(7));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("insert a33a567c-a099-4e53-a8c1-391385d3974f", []() {
      //    iterator insert(const_iterator pos, std::initializer_list<T> ilist, Allocator &allocator);
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      ::std::array<int, 7> b{{1, 2, 6, 7, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.insert(v.begin() + 2, {6, 7}, alloc);
      AssertThat(v.size(), Equals(7));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("erase f2d131e4-6b45-449a-af9c-a3df92381b86", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.erase(v.begin() + 1, alloc);
      ::std::array<int, 4> b{{1, 3, 4, 5}};
      AssertThat(v.size(), Equals(4));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("erase 353a772a-93f3-44d0-aa3d-ccf9933dacae", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.erase(v.begin() + 1, v.begin() + 3, alloc);
      ::std::array<int, 3> b{{1, 4, 5}};
      AssertThat(v.size(), Equals(3));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("erase 31cc5256-ed3d-4c74-8443-67e6cc0f30a8", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.erase(v.begin() + 4, alloc);
      AssertThat(v.size(), Equals(4));
      AssertThat(::std::equal(v.begin(), v.end(), a.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("push_back 80915e7f-4b5a-4138-a048-cc059c78289d8", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.push_back(6, alloc);
      ::std::array<int, 6> b{{1, 2, 3, 4, 5, 6}};
      AssertThat(v.size(), Equals(6));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("push_back 650b51b0-378d-449b-ab1a-416a834945a1", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      int i = 6;
      v.push_back(::std::move(i), alloc);
      ::std::array<int, 6> b{{1, 2, 3, 4, 5, 6}};
      AssertThat(v.size(), Equals(6));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("emplace_back e3484eec-2865-4a14-9ab2-cc0ad9fa6c80", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.emplace_back(alloc, 6);
      ::std::array<int, 6> b{{1, 2, 3, 4, 5, 6}};
      AssertThat(v.size(), Equals(6));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });
    it("pop_back f6602976-5bc9-496c-899d-9741d05624f6", []() {
      auto alloc = ::std::allocator<int>();
      ::std::array<int, 5> a{{1, 2, 3, 4, 5}};
      auto v = vector_extrensic_allocator_t<int>(a.begin(), a.end(), alloc);
      v.pop_back(alloc);
      ::std::array<int, 4> b{{1, 2, 3, 4}};
      AssertThat(v.size(), Equals(4));
      AssertThat(::std::equal(v.begin(), v.end(), b.begin()), IsTrue());
      v.destroy(alloc);
    });

  });
}
