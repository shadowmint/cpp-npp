## Project
cmake_minimum_required(VERSION 3.1)
project(npp)

# Dependencies
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/npp)

# Platform specific
if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES "x86_64;i386")
endif()

# Require features
set(required_features
    cxx_constexpr
    cxx_variadic_templates
    cxx_auto_type)

# Warnings~
include(${CMAKE_CURRENT_SOURCE_DIR}/sugar/cmake/Sugar)
include(sugar_generate_warning_flags)
sugar_generate_warning_flags(
  flags
  properties
  ENABLE ALL
  DISABLE c++98-compat padded
  TREAT_AS_ERROR ALL
  CLEAR_GLOBAL)

# Library / executable if any
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/npp/*.cpp)
add_library(npp STATIC ${SOURCES})
target_compile_features(npp PRIVATE ${required_features})
set_target_properties(npp PROPERTIES ${properties} COMPILE_OPTIONS "${flags}")

# Local tests
enable_testing()
add_executable(tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cpp")
target_compile_features(tests PRIVATE ${required_features})
set_target_properties(tests PROPERTIES ${properties} COMPILE_OPTIONS "${flags}")
target_link_libraries(tests npp)
add_test(tests tests)
