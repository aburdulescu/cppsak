cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(enum2s)

set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

option(ASAN "Use AddressSanitizer" OFF)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -fno-omit-frame-pointer")

if (ASAN)
  string(APPEND CMAKE_CXX_FLAGS " -fsanitize=address,undefined")
endif()

add_executable(enum2s main.cc)

find_library(LIBCLANG libclang.so)

message(STATUS "LIBCLANG=${LIBCLANG}")

target_link_libraries(enum2s PRIVATE ${LIBCLANG})
