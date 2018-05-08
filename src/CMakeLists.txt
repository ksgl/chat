add_executable(chat main.cpp json.hpp TaskManager.hpp)
target_link_libraries(chat ${Boost_LIBRARIES})