#include <iostream>
#include "task_manager.hpp"

void tasker_1(task_manager &obj) {
    json j;
    j["task"] = "some fucking task";
    
    for(int i = 0; i < 10; i++)
        obj.add_task_on_queue(j);
}

void tasker_2(task_manager &obj) {
    json j;
    j["task"] = "another fucking task";
    
    for(int i = 0; i < 10; i++)
        obj.add_task_on_queue(j);
}

task_manager &task_manager_obj = task_manager::instance();

int main() {
    thread task_1(tasker_1, task_manager_obj);
    thread task_2(tasker_2, task_manager_obj);
    
    task_1.join();
    task_2.join();
    
    task_manager_obj.show_tasks();
    
    return EXIT_SUCCESS;
}

