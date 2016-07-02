#include "./TestOption.h"
#include "../test/TestSuite.h"
#include "../Option.h"
#include "../Types.h"

using npp::Option;
using npp::Some;
using npp::None;
using TestSuite = npp::test::TestSuite;

namespace npp {
namespace tests {
namespace option {

Option<int> test_fixture(int value);
Option<int> test_fixture(int value) {
  if (value >= 0) {
    return Some<int>(value + 10);
  }
  return None<int>();
}

DEFINE_TEST(test_some_helper) {
  auto value = Some<int>(100);
  ASSERT(value);
  ASSERT(*value == 100);
}

DEFINE_TEST(test_none_helper) {
  auto value = None<int>();
  ASSERT(!value);
}

DEFINE_TEST(test_then_fixture) {
  auto value = test_fixture(100);
  ASSERT(value && *value == 110);
  value = test_fixture(-10);
  ASSERT(!value);
}

DEFINE_TEST(test_then) {
  bool found = false;
  test_fixture(100).Then([&] (int v) { found = true; ASSERT(v == 110); });
  test_fixture(-10).Then([&] (int) { UNREACHABLE; });
  if (!test_fixture(10).Then([] (int) {})) {
    UNREACHABLE;
  }
  ASSERT(found);
}

DEFINE_TEST(test_or) {
  auto value = test_fixture(100).Or(-1);
  ASSERT(value == 110);

  value = test_fixture(-100).Or(-1);
  ASSERT(value == -1);
}

DEFINE_TEST(test_equals_op) {
  auto value = test_fixture(100);  // Fixture is +10
  ASSERT(value == 110);
  ASSERT(110 == value);
  ASSERT(value != 100);
  ASSERT(100 != value);
}

DEFINE_TEST(test_deref_operators) {
  auto vec = std::vector<u32>();
  auto value = Some<std::vector<u32>*>(&vec);
  (*value)->push_back(100);
  value->push_back(101);
  ASSERT(vec.at(0) == 100);
  ASSERT(vec.at(1) == 101);
}

} // namespace option

std::string TestOption::Name(void) {
  return "TestOption";
}

void TestOption::Execute(void) {
  TEST(option::test_some_helper)
  TEST(option::test_none_helper)
  TEST(option::test_then_fixture)
  TEST(option::test_then)
  TEST(option::test_or)
  TEST(option::test_deref_operators)
  TEST(option::test_equals_op)
}

} // namespace tests
} // namespace npp
