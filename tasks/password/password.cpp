#include <algorithm>
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

bool InAscii(int c) {
    return 33 <= c && c <= 126;
}


bool ValidatePassword(const std::string& password) {
    if (password.length() < 8 || 14 < password.length()) {
        return false;
    }
    bool has_type[4];
    std::fill(has_type, has_type + 4, false);
    for (const char &c : password) {
        if (IsDigit(c)) {
            has_type[0] = true;
        } else if (IsLower(c)) {
            has_type[1] = true;
        } else if (IsUpper(c)) {
            has_type[2] = true;
        } else if (InAscii(static_cast<int>(c))) {
            has_type[3] = true;
        } else {
            return false;
        }
    }
    return std::count(has_type, has_type + 4, true) >= 3;
}
