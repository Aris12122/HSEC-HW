#include "scorer.h"

void Scorer::DeleteInTable(const StudentName& student_name, const TaskName& task_name) {
    if (!submits.contains(student_name)) {
        return;
    }
    submits[student_name].erase(task_name);
    if (submits[student_name].empty()) {
        submits.erase(student_name);
    }
}

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    auto& task_status = student_task_status[{student_name, task_name}];
    task_status.success = false;
    if (!task_status.merge_req) {
        DeleteInTable(student_name, task_name);
    }
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    auto& task_status = student_task_status[{student_name, task_name}];
    task_status.success = true;
    if (!task_status.merge_req) {
        submits[student_name].insert(task_name);
    }
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    auto& task_status = student_task_status[{student_name, task_name}];
    task_status.merge_req = true;
    if (task_status.success) {
        DeleteInTable(student_name, task_name);
    }
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    auto& task_status = student_task_status[{student_name, task_name}];
    task_status.merge_req = false;
    if (task_status.success) {
        submits[student_name].insert(task_name);
    }
}

void Scorer::Reset() {
    submits.clear();
    student_task_status.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    return submits;
}
