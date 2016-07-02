#pragma once

#include "Test.h"

namespace npp {

namespace test {

/// A result type, like in rust
class TestResult {

public:
  /// Name of this test
  std::string name;

  /// The test callback
  npp::test::Test handle;

  /// Did the test pass?
  bool success;

  /// Test a test instance
  TestResult(std::string testName, Test handler) {
    this->name = testName;
    this->handle = handler;
    this->success = false;
  }

  /// Run the test instance
  bool Run(npp::ILog *logger) {
    this->success = true;
    this->handle(this->success, logger);
    return this->success;
  }
};

} // namespace test

} // namespace npp
