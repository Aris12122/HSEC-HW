#include <algorithm>
#include <vector>
#include "password.h"

bool IsDigit(const char &c) {
    return '0' <= c && c <= '9';
}

bool IsLower(const char &c) {
    return 'a' <= c && c <= 'z';
}

bool IsUpper(const char &c) {
    return 'A' <= c && c <= 'Z';
}


bool ValidatePassword(const std::string& password) {
    int n = password.size();
    if (n < 8 || n > 14) {
        return false;
    }

    std::vector<bool> has_type(4, false);
    for (const char& c : password) {
        if (IsDigit(c)) {
            has_type[0] = true;
        } else if (IsLower(c)) {
            has_type[1] = true;
        } else if (IsUpper(c)) {
            has_type[2] = true;
        } else if (static_cast<char>(33) <= c && c <= static_cast<char>(126)) {
            has_type[3] = true;
        } else {
            return false;
        }
    }
    return std::count(begin(has_type), end(has_type), true) >= 3;
}
