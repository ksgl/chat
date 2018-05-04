#pragma once

#include <iostream>
#include <queue>
#include <nlohmann/json.hpp>
#include <mutex>

using json = nlohmann::json;

class task_manager {
public:
	static task_manager &instance();
	void add_task_to_queue(json obj);
    void show_tasks() {
        task_queue_mutex.lock();
        std::cout << task_queue.pop() << endl;
        ask_queue_mutex.unlock();
    }
private:
	task_manager() = default;
	task_manager(const task_manager &obj) = delete;
	task_manager &operator=(const task_manager &obj) = delete;

	std::queue<json> task_queue;
	std::mutex task_queue_mutex;
};

task_manager &task_manager::instance() {
	static task_manager single_obj;

	return single_obj;
}

void task_manager::add_task_to_queue(json obj) {
	task_queue_mutex.lock();

	task_queue.push_back(obj);

	task_queue_mutex.unlock();
}

/*
class task_executor {
public:
	static void run(task_executor *obj);
private:

};*/
