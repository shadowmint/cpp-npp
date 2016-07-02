#include "./Format.h"
#include "../Types.h"
#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::size_t;
using std::stringstream;

namespace npp {
namespace str {

/// Convert a char * to a string
string String(i8 *chars) {
  auto rtn = string(chars, 0, strlen(chars));
  return rtn;
}

/// Split a string into a vector of substrings
vector<string> Split(const string &text, string sep) {
  vector<string> tokens;
  size_t start = 0, end = 0;
  while ((end = text.find(sep, start)) != string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  tokens.push_back(text.substr(start));
  return tokens;
}

/// Join strings
string Join(vector<string> strings, string sep) {
  stringstream ss;
  for (size_t i = 0; i < strings.size(); ++i) {
    ss << strings[i];
    if (i != (strings.size() - 1)) {
      ss << sep;
    }
  }
  return ss.str();
}

/// Join strings
string Join(const int count, const string strings[], string sep) {
  stringstream ss;
  for (auto i = 0; i < count; ++i) {
    ss << strings[i];
    if (i != (count - 1)) {
      ss << sep;
    }
  }
  return ss.str();
}

/// Checks if a string contains an explicit substring
bool Contains(const std::string &text, std::string query) {
  return text.find(query, 0) != string::npos;
}

/// Checks if a string starts with an explicit substring
bool StartsWith(const std::string &text, std::string query) {
  return text.find(query, 0) == 0;
}

/// Checks if a string ends with an explicit substring
bool EndsWith(const std::string &text, std::string query) {
  if (text.length() >= query.length()) {
    return (0 == text.compare(text.length() - query.length(), query.length(), query));
  }
  return false;
}

/// Create a substring from offset -> end
std::string Substr(const std::string &text, u32 offset) {
  return text.substr(offset, text.length() - offset);
}

}  // namespace str
}  // namespace npp
