#include <cctype>
#include "password.h"

bool ValidatePassword(const std::string& password) {
    if (password.length() < 8 || 14 < password.length()) {
        return false;
    }
    bool has_type[4];
    std::fill(has_type, has_type + 4, false);
    for (const char &c : password) {
        int ic = static_cast<int>(c);
        if (std::isdigit(ic)) {
            has_type[0] = true;
        } else if (std::islower(ic)) {
            has_type[1] = true;
        } else if (std::isupper(ic)) {
            has_type[2] = true;
        } else if (33 <= ic && ic <= 126) {
            has_type[3] = true;
        } else {
            return false;
        }
    }
    return std::count(has_type, has_type + 4, true) >= 3;
}
