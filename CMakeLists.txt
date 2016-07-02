## Project
cmake_minimum_required(VERSION 3.1)
set(PROJECT npp)
project(${PROJECT})

# Dependencies
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT})

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
include(${CMAKE_CURRENT_SOURCE_DIR}/.sugar/cmake/Sugar)
include(sugar_generate_warning_flags)
sugar_generate_warning_flags(
  flags
  properties
  ENABLE ALL
  DISABLE c++98-compat padded
  CLEAR_GLOBAL)

# Library / executable if any
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT}/*.cpp)
add_library(${PROJECT} STATIC ${SOURCES})
target_compile_features(${PROJECT} PRIVATE ${required_features})
set_target_properties(${PROJECT} PROPERTIES ${properties} COMPILE_OPTIONS "${flags}")

# Local tests
option(NPP_TESTS off)
if(${NPP_TESTS})
  enable_testing()
  add_executable(tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cpp")
  target_compile_features(tests PRIVATE ${required_features})
  set_target_properties(tests PROPERTIES ${properties} COMPILE_OPTIONS "${flags}")
  target_link_libraries(tests ${PROJECT})
  add_test(tests tests)
endif()

# Export path
get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  set(NPP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" PARENT_SCOPE)
  set(NPP_LIBS ${PROJECT} PARENT_SCOPE)
endif()
