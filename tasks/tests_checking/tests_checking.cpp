#include <deque>
#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::size_t students_number = student_actions.size();
    std::deque<const std::string*> paper_list;
    for (const StudentAction& action : student_actions) {
        switch (action.side) {
            case Side::Bottom:
                paper_list.push_back(static_cast<const std::string*>(&action.name));
                break;
            case Side::Top:
                paper_list.push_front(static_cast<const std::string*>(&action.name));
                break;
        }
    }
    std::vector<const std::string*> paper_by_order;
    paper_by_order.reserve(students_number);
    for (const std::string* name : paper_list) {
        paper_by_order.emplace_back(name);
    }

    std::vector<std::string> students_order;
    students_order.reserve(students_number);
    for (size_t q : queries) {
        students_order.emplace_back(*paper_by_order[--q]);
    }
    return students_order;
}
