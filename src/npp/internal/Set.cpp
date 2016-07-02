#include "./Set.h"
#include "../Types.h"
#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::size_t;
using std::stringstream;

/// Convert a char * to a string
string npp::set::String(i8 *chars) {
  auto rtn = string(chars, 0, strlen(chars));
  return rtn;
}
