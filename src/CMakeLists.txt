add_executable(chat main.cpp Udp_server.hpp task_manager.hpp)
target_link_libraries(chat ${Boost_LIBRARIES} nlohmann_json)