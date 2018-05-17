cmake_minimum_required(VERSION 3.5)

project(chat LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_AUTOMOC ON)

find_package(Boost 1.58.0 REQUIRED COMPONENTS system filesystem)
find_package(Qt5Widgets)

include_directories (${Boost_INCLUDE_DIR})
include_directories("${PROJECT_SOURCE_DIR}")

#target_link_libraries(chat Qt5::Widgets)

add_subdirectory(src)
add_subdirectory(Chat)