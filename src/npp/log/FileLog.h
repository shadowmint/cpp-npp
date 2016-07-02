#pragma once

#include <string>
#include "../internal/Format.h"
#include "../Log.h"
#include <fstream>

namespace npp {

/// File logger implementation
/// Note that creating a new instance blows away an existing log file.
class FileLog : public ILog {
protected:
  /// The file handle
  std::unique_ptr<std::ofstream> fp;

  /// Log specifically to file
  virtual void log(std::string msg);

public:
  /// Create a new instance
  /// @param path The file to save the log to
  FileLog(std::string path);

  /// Close the log file
  ~FileLog();
};

} // namespace npp
