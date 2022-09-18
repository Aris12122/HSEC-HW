#include "sort_students.h"
#include <tuple>

bool operator==(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) ==
           std::tie(date2.year, date2.month, date2.day);
}

bool operator<(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) <
           std::tie(date2.year, date2.month, date2.day);
}

bool AreFullNamesEqual(const Student& student1, const Student& student2) {
    return std::tie(student1.last_name, student1.name) ==
           std::tie(student2.last_name, student2.name);
}

bool IsFullNameLess(const Student& student1, const Student& student2) {
    return std::tie(student1.last_name, student1.name) <
           std::tie(student2.last_name, student2.name);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    std::sort(begin(students), end(students), [&](const Student& student1, const Student& student2) {
        if (sortKind == SortKind::Date) {
            if (student1.birth_date == student2.birth_date) {
                return IsFullNameLess(student1, student2);
            }
            return student1.birth_date < student2.birth_date;
        } else {
            // sortKind == SortKind::Name
            if (AreFullNamesEqual(student1, student2)) {
                return student1.birth_date < student2.birth_date;
            }
            return IsFullNameLess(student1, student2);
        }
    });
}
