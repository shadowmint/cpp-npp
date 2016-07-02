#pragma once

#include <string>
#include "./internal/Format.h"

namespace npp {

/// Logger interface
class ILog {
public:
  /// This is an interface
  virtual ~ILog() {}

  /// Expand arguments and log to file
  template <typename... Args> void trace(const std::string &format, Args... args) {
    auto resolved = Format(format, args...);
    log(resolved);
  }

protected:
  virtual void log(std::string msg);
};

} // namespace npp
