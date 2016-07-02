#include "../src/npp/log/ConsoleLog.h"
#include "../src/npp/tests/NppTestRunner.h"

using npp::ConsoleLog;

int TestFailures();

int TestFailures() {
  ConsoleLog log;
  return npp::tests::NppTestRunner(log);
}

int main(int, char *[]) {
  return TestFailures() != 0;
}
