#include "./TestSuite.h"
#include "./Test.h"

namespace npp {

namespace test {

/// Add a new a test
void TestSuite::Test(std::string name, npp::test::Test target) {
  this->tests.push_back(npp::make_unique<TestResult>(name, target));
}

/// Run the test suite and return a count of failures
int TestSuite::Report(ILog *log) {
  Execute();
  auto failures = 0;
  auto count = 0;
  for (size_t i = 0; i < this->tests.size(); ++i) {
    TestResult *t = this->tests.at(i).get();
    count += 1;
    log->trace("exec: %s: %s ", Name().c_str(), t->name.c_str());
    if (t->Run(log)) {
      log->trace("OK\n");
    } else {
      failures += 1;
      log->trace("FAIL\n");
    }
  }
  return failures;
}

/// Return test suite name
std::string TestSuite::Name(void) {
  return "TestSuite";
}

} // namespace test

} // namespace npp
