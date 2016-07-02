#include "../test/TestSuite.h"

namespace npp {
namespace tests {

class TestFormat : public npp::test::TestSuite {
protected:
  void Execute(void);
  std::string Name(void);
};

} // namespace tests
} // namespace npp
