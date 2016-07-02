#include "../test/TestSuite.h"

namespace npp {
namespace tests {

class TestOption : public npp::test::TestSuite {
protected:
  void Execute(void);
  std::string Name(void);
};

} // namespace tests
} // namespace npp
