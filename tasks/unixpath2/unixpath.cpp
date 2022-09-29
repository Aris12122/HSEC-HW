#include "unixpath.h"
#include <vector>

std::vector<std::string_view> SplitString(const std::string_view& str, char separator, size_t cur_pos) {
    std::vector<std::string_view> split;
    while (cur_pos < str.length()) {
        size_t next = std::find(str.begin() + cur_pos, str.end(), separator) - str.begin();
        split.emplace_back(str.substr(cur_pos, next - cur_pos));
        cur_pos = next + 1u;
    }
    return split;
}

UnixPath::UnixPath(std::string_view initial_dir) {
    current_path_ = SplitString(initial_dir, '/', 0u);
    initial_path_ = current_path_;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    std::size_t pos = 0u;
    if (path[pos] == '/') {
        ++pos;
        current_path_ = {static_cast<std::string_view>("")};
    }

    for (const std::string_view& action : SplitString(path, '/', pos)) {
        if (action == "..") {
            if (current_path_.size() > 1) {
                current_path_.pop_back();
            }
        } else if (!action.empty() && action != ".") {
            current_path_.emplace_back(action);
        }
    }
}

std::string UnixPath::GetAbsolutePath() const {
    std::string result;
    for (const std::string_view& dir : current_path_) {
        result += static_cast<std::string>(dir) + "/";
    }
    result.pop_back();
    return result;
}

std::string UnixPath::GetRelativePath() const {
    std::size_t pos = initial_path_.size() - 1u;
    std::string relative_path;
    for (; pos >= current_path_.size() || current_path_[pos] != initial_path_[pos]; --pos) {
        relative_path += "../";
    }
    if (relative_path.empty()) {
        relative_path = "./";
    }
    for (++pos; pos < current_path_.size(); ++pos) {
        relative_path += static_cast<std::string>(current_path_[pos]) + "/";
    }
    relative_path.pop_back();
    return relative_path;
}
