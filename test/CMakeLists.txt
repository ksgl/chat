add_executable(chat-cli cli.cpp)
target_link_libraries(chat-cli chat)
target_include_directories(chat-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
