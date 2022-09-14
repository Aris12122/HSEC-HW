#include <cctype>
#include "password.h"

bool ValidatePassword(const std::string& password) {
    if (14 < password.length() || password.length() < 8) {
        return false;
    }

    bool has_type[4];
    for (size_t i = 0; i < 4; ++i) {
        has_type[i] = false;
    }

    for (const char& c : password) {
        if (126 < static_cast<int>(c) || static_cast<int>(c) < 33) {
            return false;
        }

        if (std::isdigit(c)) {
            has_type[0] = true;
        } else if (std::islower(c)) {
            has_type[1] = true;
        } else if (std::isupper(c)) {
            has_type[2] = true;
        } else {
            has_type[3] = true;
        }
    }

    int cnt = 0;
    for (size_t i = 0; i < 4; ++i) {
        cnt += static_cast<int>(has_type[i]);
    }

    return cnt >= 3;
}
