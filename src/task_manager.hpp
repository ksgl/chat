#pragma once

#include <iostream>
#include <queue>
#include "json.hpp"
#include <mutex>

using json = nlohmann::json;

class TaskManager {
public:
	static TaskManager &instance();
	void add_task_to_queue(json task);
private:
	TaskManager() = default;
	TaskManager(const TaskManager &obj) = delete;
	TaskManager &operator=(const TaskManager &obj) = delete;

	std::queue<json> task_queue;
	std::mutex task_queue_mutex;
};

TaskManager &TaskManager::instance() {
	static TaskManager single_obj;

	return single_obj;
}

void TaskManager::add_task_to_queue(json task) {
	task_queue_mutex.lock();

	task_queue.push(task);

	task_queue_mutex.unlock();
}

/*
class task_executor {
public:
	static void run(task_executor *obj);
private:

};*/
