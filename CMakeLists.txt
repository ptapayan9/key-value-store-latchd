# Require CMake 3.20 or newer to configure this project.
cmake_minimum_required(VERSION 3.20)

# Name the project and enable the C++ compiler (CXX means C++).
project(Latch LANGUAGES CXX)

# Export compiler commands so editor tools such as clangd can resolve headers.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build the storage implementation as a library shared by the app and future
# tests.
add_library(latch_store src/store.cpp)

# PUBLIC requirements apply to this library and to targets that link to it. Add
# src to the header search path so consumers can include "store.hpp".
target_include_directories(latch_store PUBLIC src)
# Require at least C++20 for the library and its consumers.
target_compile_features(latch_store PUBLIC cxx_std_20)
# Request a standard C++ dialect instead of a compiler-specific extended
# dialect.
set_target_properties(latch_store PROPERTIES CXX_EXTENSIONS OFF)

# Enable common, additional, and standards-related warnings for Clang/GCC.
# PRIVATE means these options apply only to this target, not its consumers.
target_compile_options(latch_store PRIVATE -Wall -Wextra -Wpedantic)

# Build the application executable, whose entry point is in main.cpp.
add_executable(latchd src/main.cpp)

# Link the app to Store's implementation and inherit its PUBLIC requirements.
target_link_libraries(latchd PRIVATE latch_store)
# Disable language extensions for the app too; this property is target-specific.
set_target_properties(latchd PROPERTIES CXX_EXTENSIONS OFF)

# Enable warnings for main.cpp as well; the library's PRIVATE flags do not
# propagate.
target_compile_options(latchd PRIVATE -Wall -Wextra -Wpedantic)

# Enable CTest and provide the BUILD_TESTING option (ON by default).
include(CTest)

if(BUILD_TESTING)
  # Download and build a specific Catch2 release.
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
    GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(Catch2)

  # Build tests separately from the application.
  add_executable(latch_tests tests/store_test.cpp)

  # Reuse our storage library; Catch2 supplies the test runner's main().
  target_link_libraries(latch_tests PRIVATE latch_store Catch2::Catch2WithMain)

  set_target_properties(latch_tests PROPERTIES CXX_EXTENSIONS OFF)
  target_compile_options(latch_tests PRIVATE -Wall -Wextra -Wpedantic)

  # Register each Catch2 test case with CTest.
  list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
  include(Catch)
  catch_discover_tests(latch_tests)
endif()
