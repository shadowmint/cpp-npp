#pragma once

#include "../Log.h"
#include "TestResult.h"
#include "../Unique.h"
#include <vector>

namespace npp {

namespace test {

/// A result type, like in rust
class TestSuite {

private:
  /// The list of test functions to run
  std::vector<std::unique_ptr<TestResult>> tests;

protected:
  /// This is an interface
  virtual ~TestSuite() {}

  /// Run all tests
  virtual void Execute(void) = 0;

  /// Return test suite name
  virtual std::string Name(void);

  /// Add a new a test
  void Test(std::string name, Test target);

public:
  /// Run the test suite and return a count of failures
  int Report(ILog *log);
};

} // namespace test

} // namespace npp
