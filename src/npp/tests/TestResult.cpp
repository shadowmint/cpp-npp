#include "./TestResult.h"
#include "../test/TestSuite.h"
#include "../Result.h"
#include "../Types.h"

using npp::Result;
using npp::Ok;
using npp::Err;
using TestSuite = npp::test::TestSuite;

namespace npp {
namespace tests {
namespace result {

Result<int, const char *> test_fixture(int value);
Result<int, const char *> test_fixture(int value) {
  if (value >= 0) {
    return Ok<int, const char *>(value + 10);
  }
  return Err<int, const char *>("Invalid request, must be +ve");
}

DEFINE_TEST(test_ok_helper) {
  auto value = Ok<int, int>(100);
  ASSERT(value);
  ASSERT(value.Ok() == 100);
}

DEFINE_TEST(test_err_helper) {
  auto value = Err<int, int>(100);
  ASSERT(!value);
  ASSERT(value.Err() == 100);
}

DEFINE_TEST(test_then_fixture) {
  auto value = test_fixture(100);
  ASSERT(value && value.Ok() == 110);
  value = test_fixture(-10);
  ASSERT(!value);
}

DEFINE_TEST(test_then) {
  test_fixture(100).Then([&] (int v) { ASSERT(v == 110); }, [&] (const char *) { UNREACHABLE; });
  test_fixture(-10).Then([&] (int) { UNREACHABLE; }, [&] (const char * err) { ASSERT(err != NULL); });
}

DEFINE_TEST(test_then_as_lambdas) {
  int v0 = 0;
  test_fixture(100).Then([&] (int) { v0 = 100; }, [&] (const char *) { UNREACHABLE; });
  ASSERT(v0 == 100);

  int v1 = 0;
  test_fixture(-10).Then([&] (int) { UNREACHABLE; }, [&] (const char *) { v1 = 100; });
  ASSERT(v1 == 100);
}

} // namespace result

std::string TestResult::Name(void) {
  return "TestResult";
}

void TestResult::Execute(void) {
  TEST(result::test_ok_helper)
  TEST(result::test_err_helper)
  TEST(result::test_then_fixture)
  TEST(result::test_then)
  TEST(result::test_then_as_lambdas)
}

} // namespace tests
} // namespace npp
