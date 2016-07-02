// Copyright 2016 linderd@iinet.net.au
#include "./TestFormat.h"
#include <string>
#include <vector>
#include "../internal/Format.h"

using npp::Format;
using std::string;
using std::vector;

namespace npp {
namespace tests {
namespace str {

DEFINE_TEST(test_format_string) {
  auto value = Format("%d %s", 100, "Hello World");
  ASSERT(strcmp(&value[0], "100 Hello World") == 0);
}

DEFINE_TEST(test_split_string) {
  auto value = "one,two, three,four";

  auto parts = npp::str::Split(value, ",");
  ASSERT(parts.size() == 4);

  auto parts2 = npp::str::Split(value, ", ");
  ASSERT(parts2.size() == 2);
}

DEFINE_TEST(test_join_string_array) {
  string parts[] = {"one", "two"};
  auto full = npp::str::Join(2, parts, "-");
  ASSERT(full == "one-two");
}

DEFINE_TEST(test_join_string_vector) {
  vector<string> parts = {"one", "two"};
  auto full = npp::str::Join(parts, "-");
  ASSERT(full == "one-two");
}

DEFINE_TEST(test_contains) {
  auto path = "C:\\full\\path\\yeah.txt";
  ASSERT(npp::str::Contains(path, "C:\\"));
  ASSERT(npp::str::Contains(path, "path"));
  ASSERT(npp::str::Contains(path, "yeah.txt"));
  ASSERT(!npp::str::Contains(path, "1yeah.txt"));
  ASSERT(!npp::str::Contains(path, "C::"));
}

DEFINE_TEST(test_starts_with) {
  auto path = "C:\\full\\path\\yeah.txt";
  ASSERT(npp::str::StartsWith(path, "C:\\"));
  ASSERT(!npp::str::StartsWith(path, "C:\\foo"));
  ASSERT(!npp::str::StartsWith(path, "path"));
}

DEFINE_TEST(test_ends_with) {
  auto path = "C:\\full\\path\\yeah.txt";
  ASSERT(npp::str::EndsWith(path, "yeah.txt"));
  ASSERT(!npp::str::EndsWith(path, "1yeah.txt"));
  ASSERT(!npp::str::EndsWith(path, "C::"));
}

DEFINE_TEST(test_substr) {
  auto path = "helloworld";
  ASSERT(npp::str::Substr(path, 5) == "world");
}

}  // namespace str

std::string TestFormat::Name(void) {
  return "TestFormat";
}

void TestFormat::Execute(void) {
  TEST(str::test_format_string);
  TEST(str::test_split_string);
  TEST(str::test_join_string_array);
  TEST(str::test_join_string_vector);
  TEST(str::test_contains);
  TEST(str::test_starts_with);
  TEST(str::test_ends_with);
  TEST(str::test_substr);
}

}  // namespace tests
}  // namespace npp
