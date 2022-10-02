#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

struct TaskStatus {
public:
    bool success = false;
    bool merge_req = false;
};

class Scorer {
public:
    ScoreTable submits;
    std::map<std::pair<StudentName, TaskName>, TaskStatus> student_task_status;

    void DeleteInTable(const StudentName& student_name, const TaskName& task_name);
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();

    ScoreTable GetScoreTable() const;
};
