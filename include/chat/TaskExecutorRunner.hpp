#pragma once

#include <chat/TaskExecutor.hpp>

#include <boost/asio.hpp>

#include <atomic>
#include <exception>
#include <thread>


namespace chat::implementation {

    // TaskExecuterRunner runs a TaskExecutor in a dedicated thread to separate it from the GUI thread.
    class TaskExecuterRunner {
    public:
        explicit TaskExecuterRunner(boost::asio::io_service& io_service);
        ~TaskExecuterRunner();

        void start();
        void stop();
        bool is_running() const;

        std::exception_ptr pop_exception();

        void set_task_executor(interface::TaskExecutor* task_executor);

    private:
        void run();

    private:
        boost::asio::io_service& io_service_;
        std::thread thread_;
        std::atomic<bool> running_;
        std::exception_ptr ex_;
        interface::TaskExecutor* task_executor_ = nullptr;
    };

} // namespace chat::implementation

