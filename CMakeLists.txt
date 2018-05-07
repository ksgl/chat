cmake_minimum_required(VERSION 3.10)

project(chat LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.66.0 REQUIRED COMPONENTS system filesystem)
include_directories (${Boost_INCLUDE_DIR})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(src)

