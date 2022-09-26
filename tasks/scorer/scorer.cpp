#include <unordered_map>
#include "scorer.h"

struct TaskLast {
    time_t success = 0;
    time_t fail = 0;
    time_t merge_req_open = 0;
    time_t merge_req_closed = 1;
};

template <class T>
void AssignMax(T& a, const T& b) {
    if (a < b) {
        a = b;
    }
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<std::pair<StudentName, TaskName>, TaskLast> student_task_status;
    for (const Event& event : events) {
        if (event.time > score_time) {
            continue;
        }
        auto& task_last = student_task_status[{event.student_name, event.task_name}];
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
    for (const auto& [names, task_last] : student_task_status) {
        if (task_last.success > task_last.fail) {
            if (task_last.merge_req_closed > task_last.merge_req_open) {
                score_table[names.first].insert(names.second);
            }
        }
    }
    return score_table;
}
