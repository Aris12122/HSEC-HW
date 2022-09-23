#include <vector>
#include "unixpath.h"

std::vector<std::string> SplitString(const std::string_view& str, char separator, size_t cur_pos) {
    std::vector<std::string> split;
    while (cur_pos < str.length()) {
        size_t next = std::find(str.begin() + cur_pos, str.end(), separator) - str.begin();
        split.emplace_back(str.substr(cur_pos, next - cur_pos));
        cur_pos = next + 1;
    }
    return split;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string> current_path = SplitString(current_working_dir, '/', 1u);

    for (const std::string& action : SplitString(path, '/', 0u)) {
        if (action == "..") {
            if (!current_path.empty()) {
                current_path.pop_back();
            }
        } else if (!action.empty() && action != ".") {
            current_path.emplace_back(action);
        }
    }
    std::string result;
    for (const std::string& dir : current_path) {
        result += "/" + dir;
    }
    if (result.empty()) {
        result = "/";
    }
    return result;
}
