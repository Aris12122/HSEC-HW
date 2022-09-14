#include "password.h"
#include <cctype>

bool ValidatePassword(const std::string& password) {
    const size_t min_password_len = static_cast<size_t>(8);
    const size_t max_password_len = static_cast<size_t>(14);

    if (max_password_len < password.length() || password.length() < min_password_len) {
        return false;
    }

    bool has_type[4];
    for (size_t i = 0; i < 4; ++i) {
        has_type[i] = false;
    }

    const char min_ascii_char = static_cast<char>(33);
    const char max_ascii_char = static_cast<char>(126);

    for (const char& c : password) {
        if (max_ascii_char < c || c < min_ascii_char) {
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
