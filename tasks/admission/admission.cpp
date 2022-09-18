#include "admission.h"

bool operator<(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) <
           std::tie(date2.year, date2.month, date2.day);
}

bool operator==(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) ==
           std::tie(date2.year, date2.month, date2.day);
}

bool operator<(const Student& student1, const Student& student2) {
    return std::tie(student1.name, student1.birth_date) <
           std::tie(student2.name, student2.birth_date);
}

bool operator<(const Applicant& applicant1, const Applicant& applicant2) {
    return std::tie() <
           std::tie();
}



AdmissionTable FillUniversities(const std::vector<University>& universities,const std::vector<Applicant>& applicants) {
    std::sort(applicants.begin(), applicants.end());
    return {};
}
