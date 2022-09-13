#include "password.h"

bool ValidatePassword(const std::string& password) {
    if (password.length() < 8 || 14 < password.length()) {
        return false;
    }
    bool has_type[4];
    std::fill(has_type, has_type + 4, false);

    for (const char &c : password) {
        if (static_cast<int>(c) < 33 || 126 < static_cast<int>(c)) {
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
    return std::count(has_type, has_type + 4, true) >= 3;
}
