#pragma once

#include <memory>

namespace npp {

/// C++11 compatibility
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/// C++11 compatibility
template <typename T>
std::unique_ptr<T[]> make_unique_array(int length) {
  return std::unique_ptr<T[]>(new T[length]);
}

} // namespace npp
