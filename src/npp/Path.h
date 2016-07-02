#pragma once

#include "./Types.h"
#include <string>
#include <vector>
#include "./Option.h"

namespace npp {

class Path {
private:
  /// The parts of the current path, as individual path
  std::vector<std::string> parts;

  /// The drive for this path, if any
  Option<std::string> drive;

  /// Is this a relative path or an absolute one?
  bool absolutePath;

  /// Split the initial path string up into parts
  /// If this path has a drive (eg. C:\\foo\\bar) use the drive as the first part
  void SplitPath(std::string raw);

public:
  /// Create a new instance from a raw os path
  Path(std::string raw);

  /// Return the number of path segments currently in this path
  u32 Segments(void);

  /// Return the drive for this path
  npp::Option<std::string> Drive(void);

  /// Set the drive for this path
  void SetDrive(std::string drive);

  /// Return if this is an absolute path
  bool Absolute(void);

  /// Set if this is an absolute path or not
  void SetAbsolute(bool absolute);

  /// Return the path as a 'resolved' path string for the current OS
  std::string OsPath(void);

  /// Pop one segment off the path sequence
  void Push(std::string segment);

  /// Push on segment onto the path sequence
  npp::Option<std::string> Pop(void);

  /// Replace the file component of a path with a new file
  void ReplaceFile(std::string filename);

  /// Return the path for the current directory
  static Path CurrentWorkingDirectory(void);

  /// Return a blank path
  static Path Blank(void);
};

} // namespace npp
