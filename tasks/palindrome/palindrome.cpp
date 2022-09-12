#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t l = 0, r = str.size() - 1;

    while (l < r) {
        if (str[l] == ' ') {
            l++;
        } else if (str[r] == ' ') {
            r--;
        } else if (str[l] != str[r]) {
            return false;
        } else {
            l++;
            r--;
        }
    }
    return true;
}
