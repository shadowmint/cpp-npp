#pragma once

#include <string>
#include "../internal/Format.h"
#include "../Log.h"

namespace npp {

/// Console logger implementation
class ConsoleLog : public ILog {
protected:
  /// Log specifically to Console
  virtual void log(std::string msg);

public:
  /// Create a new instance
  ConsoleLog();

  /// Close the log Console
  ~ConsoleLog();
};

} // namespace npp
