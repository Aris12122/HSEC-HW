#include "password.h"

bool ValidatePassword(const std::string& password) {
    if (password.length() < 8 || 14 < password.length()) {
        return false;
    }
    bool has_digits = false;
    bool has_low_letters = false;
    bool has_upp_letters = false;
    bool has_others = false;
    for (const char &c : password) {
        if (std::isdigit(c)) {
            has_digits = true;
        } else if (std::islower(c)) {
            has_low_letters = true;
        } else if (std::isupper(c)) {
            has_upp_letters = true;
        } else if (33 <= static_cast<int>(c) && static_cast<int>(c) <= 126) {
            has_others = true;
        } else {
            return false;
        }
    }
    return static_cast<int>(has_digits) + static_cast<int>(has_low_letters) + static_cast<int>(has_upp_letters) + static_cast<int>(has_others) >= 3;
}
