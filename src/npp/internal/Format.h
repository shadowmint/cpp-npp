#pragma once

#include "../OS.h"
#include "../Types.h"
#include "../Unique.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#if !NPP_WIN
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif

namespace npp {

#if NPP_WIN
#define snprintf _snprintf
#endif

/// Use printf style formatting to format a string value
template <typename... Args> std::string Format(const std::string &format, Args... args) {
  const char *format_ = static_cast<const char *>(format.c_str());
  auto size = 1 + static_cast<i32>(snprintf(nullptr, 0, format_, args...));
  auto buf = npp::make_unique_array<char>(size);
  snprintf(buf.get(), static_cast<size_t>(size), format_, args...);
  return std::string(buf.get(), buf.get() + size);
}

namespace str {

/// Convert a char * to a string
std::string String(i8 *chars);

/// Split a string into a vector of substrings
std::vector<std::string> Split(const std::string &text, std::string sep);

/// Join a series of strings into one string
std::string Join(const std::vector<std::string> strings, std::string sep);

/// Join a series of strings into one string
std::string Join(const int count, const std::string strings[], std::string sep);

/// Checks if a string contains an explicit substring
bool Contains(const std::string &text, std::string query);

/// Checks if a string starts with an explicit substring
bool StartsWith(const std::string &text, std::string query);

/// Checks if a string ends with an explicit substring
bool EndsWith(const std::string &text, std::string query);

/// Create a substring from offset -> end
std::string Substr(const std::string &text, u32 offset);

} // Namespace str

} // namespace npp
