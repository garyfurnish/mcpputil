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
  });
}
