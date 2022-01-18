cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(enums)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
set(CMAKE_BUILD_TYPE Release)

option(ASAN "Use AddressSanitizer" OFF)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -fno-omit-frame-pointer")

if (ASAN)
  string(APPEND CMAKE_CXX_FLAGS " -fsanitize=address,undefined")
endif()

if (NOT ENUMS_VERSION)
  message(FATAL_ERROR "Tool version not set")
endif()
message(STATUS "Tool version=${ENUMS_VERSION}")

add_subdirectory(llvm-project/llvm)

add_executable(enums main.cpp)
target_compile_definitions(enums PRIVATE ENUMS_VERSION="${ENUMS_VERSION}")
target_include_directories(enums PRIVATE llvm-project/clang/include)
target_link_libraries(enums PRIVATE libclang -static)
