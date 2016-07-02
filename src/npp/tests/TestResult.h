#include "../test/TestSuite.h"

namespace npp {
namespace tests {

class TestResult : public npp::test::TestSuite {
protected:
  void Execute(void);
  std::string Name(void);
};

} // namespace tests
} // namespace npp
