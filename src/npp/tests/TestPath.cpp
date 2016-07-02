#include "./TestPath.h"
#include "../Path.h"
#include "../OS.h"
#include "../internal/Format.h"
#include <string.h>

using npp::Path;

namespace npp {
namespace tests {
namespace file {

DEFINE_TEST(test_new_path) {
#if !NPP_WIN
  Path value("/usr/local/hello.txt");
  ASSERT(!value.Drive());
  ASSERT(value.Segments() == 3);
  ASSERT(value.Absolute());
  ASSERT(value.OsPath() == "/usr/local/hello.txt");

  Path value_rel("usr/local/hello.txt");
  ASSERT(!value_rel.Drive());
  ASSERT(value_rel.Segments() == 3);
  ASSERT(!value_rel.Absolute());
  ASSERT(value_rel.OsPath() == "usr/local/hello.txt");
#else
  Path value("C:\\usr\\local\\Hello.txt");
  ASSERT(value.Segments() == 3);
  ASSERT(value.Drive());
  ASSERT(value.OsPath() == "C:\\usr\\local\\Hello.txt");

  Path value2("C:usr\\local\\Hello.txt");
  ASSERT(value2.Segments() == 3);
  ASSERT(value2.Drive());
  ASSERT(!value2.Absolute());
  ASSERT(value2.OsPath() == "C:usr\\local\\Hello.txt");

  Path value3("usr\\local\\Hello.txt");
  ASSERT(value3.Segments() == 3);
  ASSERT(value3.OsPath() == "usr\\local\\Hello.txt");
#endif
}

DEFINE_TEST(test_get_cwd) {
  auto value = Path::CurrentWorkingDirectory();
  ASSERT(value.Absolute());
  ASSERT(value.Segments() > 0);
}

DEFINE_TEST(test_modify_path) {
  auto value = Path::CurrentWorkingDirectory();
  value.Pop();
  value.Push("hello.text");
  ASSERT(npp::str::EndsWith(value.OsPath(), "hello.text"));
}

DEFINE_TEST(test_replace_file) {
  auto value = Path::CurrentWorkingDirectory();
  value.Pop();
  value.Push("hello.text");
  ASSERT(npp::str::EndsWith(value.OsPath(), "hello.text"));

  auto val2 = Path::CurrentWorkingDirectory();
  val2.ReplaceFile("hello.txt");
  ASSERT(npp::str::EndsWith(value.OsPath(), "hello.text"));
}

DEFINE_TEST(test_create_blank) {
  auto value = Path::Blank();
  value.Push("c");
  value.Push("foo");
  value.Push("hello.text");
  ASSERT(npp::str::EndsWith(value.OsPath(), "hello.text"));
}

} // namespace file

std::string TestPath::Name(void) {
  return "TestPath";
}

void TestPath::Execute(void) {
  TEST(file::test_new_path);
  TEST(file::test_get_cwd);
  TEST(file::test_modify_path);
  TEST(file::test_replace_file);
  TEST(file::test_create_blank);
}

} // namespace tests
} // namespace npp
