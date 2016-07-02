#include "../Log.h"
#include "../tests/TestFormat.h"
#include "../tests/TestPath.h"
#include "../tests/TestUnique.h"
#include "../tests/TestOption.h"
#include "../tests/TestResult.h"
#include "../Unique.h"
#include "./NppTestRunner.h"
#include <stdio.h>

using npp::make_unique;

namespace npp {
namespace tests {

int NppTestRunner(ILog &log) {
  auto failures = 0;

  // Execute all test cases
  failures += make_unique<npp::tests::TestFormat>()->Report(&log);
  failures += make_unique<npp::tests::TestPath>()->Report(&log);
  failures += make_unique<npp::tests::TestUnique>()->Report(&log);
  failures += make_unique<npp::tests::TestOption>()->Report(&log);
  failures += make_unique<npp::tests::TestResult>()->Report(&log);

  return !(failures == 0);
}

} // namepsace tests
} // namespace npp
