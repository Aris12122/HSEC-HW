#include <string>
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

    bool has_type[4];
    for (size_t i = 0; i < 4; ++i) {
        has_type[i] = false;
    }

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
    int cnt = 0;
    for (size_t i = 0; i < 4; ++i) {
        cnt += static_cast<int>(has_type[i]);
    }
    return cnt >= 3;
}
