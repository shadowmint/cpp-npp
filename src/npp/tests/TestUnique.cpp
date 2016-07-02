#include "./TestUnique.h"
#include "../Unique.h"
#include "../OS.h"

#if !NPP_WIN
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

using npp::make_unique;
using npp::make_unique_array;

namespace npp {
namespace tests {
namespace unique {

class Foo {
  public:
    i32 x;
    Foo(i32 x_) : x(x_) {}
    virtual ~Foo() {}
    virtual i32 doit(i32 v) {
      return x + v;
    }
};

class Bar : public Foo {
  public:
    Bar(i32 x) : Foo(x) {}
    i32 doit(i32 v) override {
      return x - v;
    }
};

template<typename T, typename... Args>
std::unique_ptr<Foo> test_factory(Args&&... args) {
  return make_unique<T>(std::forward<Args>(args)...);
}

DEFINE_TEST(test_make_unique) {
  auto f = make_unique<Foo>(100);
  ASSERT(f->doit(1) == 101);
}

DEFINE_TEST(test_make_unique_from_derived) {
  auto b = make_unique<Bar>(100);
  ASSERT(b->doit(1) == 99);

  std::unique_ptr<Foo> c = make_unique<Bar>(100);
  ASSERT(c->doit(1) == 99);

  auto d = test_factory<Bar>(100);
  ASSERT(d->doit(1) == 99);
}

DEFINE_TEST(test_make_unique_array) {
  auto a = make_unique_array<int>(10);
  a[0] = 1;
  a[9] = 1;
  ASSERT(a[0] == 1);
  ASSERT(a[9] == 1);
}

} // namespace unique

std::string TestUnique::Name(void) {
  return "TestUnique";
}

void TestUnique::Execute(void) {
  TEST(unique::test_make_unique);
  TEST(unique::test_make_unique_from_derived);
  TEST(unique::test_make_unique_array);
}

} // namespace tests
} // namespace npp
