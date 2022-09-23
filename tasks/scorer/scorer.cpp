#include <unordered_map>
#include "scorer.h"

struct TaskLast {
    time_t success = 0;
    time_t fail = 0;
    time_t merge_req_open = 0;
    time_t merge_req_closed = 0;
};

template<class T>
bool AssignMax(T &a,const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::unordered_map<StudentName, std::unordered_map<TaskName, TaskLast>> student_task_status;
    for (const Event& event : events) {
        if (event.time > score_time) {
            continue;
        }
        auto & task_last = student_task_status[event.student_name][event.task_name];
        switch (event.event_type) {
            case EventType::CheckFailed:
                AssignMax(task_last.fail, event.time);
                break;
            case EventType::CheckSuccess:
                AssignMax(task_last.success, event.time);
                break;
            case EventType::MergeRequestOpen:
                AssignMax(task_last.merge_req_open, event.time);
                break;
            case EventType::MergeRequestClosed:
                AssignMax(task_last.merge_req_closed, event.time);
                break;
        }
    }

    ScoreTable score_table;
    for (const auto& [student_name, task_status]: student_task_status) {
        for (const auto& [task_name, task_last] : task_status) {
            if (task_last.success > task_last.fail) {
                if (task_last.merge_req_closed >= task_last.merge_req_open) {
                    score_table[student_name].insert(task_name);
                }
            }
        }
    }
    return score_table; // test
}
