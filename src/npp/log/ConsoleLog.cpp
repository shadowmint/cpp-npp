#include "./ConsoleLog.h"
#include "../internal/Format.h"
#include "../OS.h"
#include "../Types.h"
#include <string>

using std::string;
using std::cout;

npp::ConsoleLog::ConsoleLog() {
}

npp::ConsoleLog::~ConsoleLog() {
}

void npp::ConsoleLog::log(string msg) {
  cout << msg;
}
