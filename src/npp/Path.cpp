#include "./Path.h"
#include "./OS.h"
#include "./internal/Format.h"
#include <string>
#include <iostream>
#include <vector>

#if NPP_WIN
#include <windows.h>
#else
#include <limits.h>
#include <stdlib.h>
char *realpath(const char *path, char *resolved_path);
#endif

#if NPP_WIN
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

using npp::Path;
using npp::Option;
using npp::Some;
using npp::None;
using std::string;

Path::Path(string path) {
  SplitPath(path);
}

/// Return the number of path segments currently in this path
u32 Path::Segments(void) {
  return static_cast<u32>(parts.size());
}

void Path::SplitPath(std::string raw) {
  parts.clear();
  drive = None<string>();

  // Look for a drive
  if (raw.length() >= 2) {
    if (raw[1] == ':') {
      raw = npp::str::Substr(raw, 2);
      drive = Some<string>(npp::str::String(&raw[0]));
    }
  }

  // Check if absolute?
  absolutePath = false;
  if (raw.length() >= 1) {
    if (raw[0] == PATH_SEP[0]) {
      absolutePath = true;
      raw = npp::str::Substr(raw, 1);
    }
  }

  // Push path fragments into internal buffer
  auto fragments = npp::str::Split(raw, PATH_SEP);
  parts.insert(parts.end(), fragments.begin(), fragments.end());
}

/// Return the drive for this path
Option<std::string> Path::Drive(void) {
  return drive;
}

/// Set the drive for this path
void Path::SetDrive(string dr) {
  drive = Some<string>(dr);
}

/// Return if this is an absolute path
bool Path::Absolute(void) {
  return absolutePath;
}

/// Set if this is an absolute path or not
void Path::SetAbsolute(bool absolute) {
  absolutePath = absolute;
}

string Path::OsPath(void) {
  auto rtn = npp::str::Join(parts, PATH_SEP);
  if (absolutePath) {
    rtn = PATH_SEP + rtn;
  }
  if (drive) {
    rtn = *drive + ":" + rtn;
  }
  return rtn;
}

/// Pop one segment off the path sequence
void Path::Push(std::string segment) {
  parts.push_back(segment);
}

/// Push on segment onto the path sequence
npp::Option<std::string> Path::Pop(void) {
  auto rtn = None<string>();
  if (parts.size() > 0) {
    rtn = Some<string>(parts.back());
    parts.pop_back();
  }
  return rtn;
}

/// Replace the file component of a path with a new file
void Path::ReplaceFile(std::string filename) {
  Pop();
  Push(filename);
}

Path Path::CurrentWorkingDirectory(void) {
#if NPP_WIN
  char buffer[MAX_PATH];
  GetModuleFileName(NULL, buffer, MAX_PATH);
  string::size_type pos = string(buffer).find_last_of("\\/");
  auto path = string(buffer).substr(0, pos);
  return Path(path);
#else
  auto path = realpath(".", NULL);
  if (path != NULL) {
    auto spath = npp::str::String(path);
    free(path);
    return Path(spath);
  }
#endif
  return Path("");
}

Path Path::Blank(void) {
  return Path("");
}
