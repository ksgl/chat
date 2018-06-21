#include <chat/TaskExecutorRunner.hpp>

#include <stdexcept>


namespace chat::implementation {

    TaskExecuterRunner::TaskExecuterRunner(boost::asio::io_service& io_service)
        : io_service_(io_service)
    {
    }

    TaskExecuterRunner::~TaskExecuterRunner() {
        stop();

        auto ex = pop_exception();
        if (ex) {
            try {
                std::rethrow_exception(ex);
            }
            catch (const std::exception& ex) {
                std::printf("Task executor exception: %s", ex.what());
            }
            catch (...) {
                std::printf("Task executor exception: <unknown>");
            }
        }
    }

    void TaskExecuterRunner::start() {
        if (is_running()) {
            throw std::runtime_error("task executor is already running");
        }

        if (!task_executor_) {
            throw std::runtime_error("task executor is not set");
        }

        io_service_.post([this](){ this->task_executor_->start(); });
        thread_ = std::thread([this](){ this->run(); });
    }

    void TaskExecuterRunner::stop() {
        if (is_running()) {
            io_service_.post([this](){ this->task_executor_->stop(); });
        }

        if (thread_.joinable()) {
            thread_.join();
        }

        thread_ = std::thread();
        running_ = false;
    }

    bool TaskExecuterRunner::is_running() const {
        return running_;
    }

    std::exception_ptr TaskExecuterRunner::pop_exception() {
        if (is_running()) {
            throw std::runtime_error("task executor is still running");
        }

        auto ex = ex_;
        ex_ = std::exception_ptr{};

        return ex;
    }

    void TaskExecuterRunner::set_task_executor(interface::TaskExecutor* task_executor) {
        if (is_running()) {
            throw std::runtime_error("task executor is currently running");
        }

        task_executor_ = task_executor;
    }

    void TaskExecuterRunner::run() {
        running_ = true;
        ex_ = std::exception_ptr{};

        try {
            io_service_.run();
        } catch (...) {
            ex_ = std::current_exception();
        }

        running_ = false;
    }

} // namespace chat::implementation

