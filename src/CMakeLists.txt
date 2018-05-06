add_executable(chat main.cpp UDPServer.hpp json.hpp)
target_link_libraries(chat ${Boost_LIBRARIES})
