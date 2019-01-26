<<<<<<< HEAD
add_executable(chat main.cpp)
target_link_libraries(chat ${Boost_LIBRARIES})
=======
add_library(chat
    UDPRPCServer.cpp
    JSONTaskExecutor.cpp
    RPCServer.cpp
    TaskExecutor.cpp
    TaskExecutorRunner.cpp

    # Headers, just for IDE.
    ${PROJECT_SOURCE_DIR}/include/chat/UDPRPCServer.hpp
    ${PROJECT_SOURCE_DIR}/include/chat/JSONTaskExecutor.hpp
    ${PROJECT_SOURCE_DIR}/include/chat/RPCServer.hpp
    ${PROJECT_SOURCE_DIR}/include/chat/TaskExecutor.hpp
    ${PROJECT_SOURCE_DIR}/include/chat/TaskExecutorRunner.hpp
    ${PROJECT_SOURCE_DIR}/include/nlohmann/json.hpp
)
target_include_directories(chat PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(chat PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(chat PUBLIC Boost::boost)
target_link_libraries(chat PUBLIC Boost::disable_autolinking)
target_link_libraries(chat PUBLIC Boost::filesystem)
>>>>>>> 90d7950429a3785269e42ccb4e1952015e385cdf
