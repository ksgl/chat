add_executable(chat main.cpp json.hpp task_manager.hpp)
target_link_libraries(chat ${Boost_LIBRARIES})