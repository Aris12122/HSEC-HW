#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {
private:
    std::vector<std::string_view> current_path_;
    std::vector<std::string_view> initial_path_;

public:
    explicit UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;
};
