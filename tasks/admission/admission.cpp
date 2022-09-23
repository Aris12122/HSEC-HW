#include "admission.h"

bool operator<(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) < std::tie(date2.year, date2.month, date2.day);
}

bool operator==(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) == std::tie(date2.year, date2.month, date2.day);
}

bool operator<(const Student& student1, const Student& student2) {
    return std::tie(student1.name, student1.birth_date) < std::tie(student2.name, student2.birth_date);
}

bool operator<(const Applicant& applicant1, const Applicant& applicant2) {
    return std::tie(applicant2.points, applicant1.student.birth_date, applicant1.student.name) < std::tie(applicant1.points, applicant2.student.birth_date, applicant2.student.name);
}

AdmissionTable FillUniversities(const std::vector<University>& universities,const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> applicants_pointers(applicants.size());
    for (std::size_t i = 0; i < applicants_pointers.size(); ++i) {
        applicants_pointers[i] = static_cast<const Applicant*>(&applicants[i]);
    }
    std::sort(applicants_pointers.begin(), applicants_pointers.end(),
              [](const Applicant* applicant1, const Applicant* applicant2) { return *applicant1 < *applicant2; });
    AdmissionTable admission_table;
    std::unordered_map<std::string, std::size_t> university_capacity;

    for (const University& university : universities) {
        university_capacity[university.name] = university.max_students;
    }

    for (const Applicant* applicant_ptr : applicants_pointers) {
        const Student& student = applicant_ptr->student;
        const std::vector<std::string>& wish_list = applicant_ptr->wish_list;

        for (const std::string& priority_university : wish_list) {
            auto& admission_list = admission_table[priority_university];
            if (admission_list.size() < university_capacity[priority_university]) {
                admission_list.emplace_back(static_cast<const Student*>(&student));
                break;
            }
        }
    }

    for (auto& [university, student_list] : admission_table) {
        std::sort(begin(student_list), end(student_list),
                  [](const Student* student1, const Student* student2) { return *student1 < *student2; });
    }
    return admission_table;
}
