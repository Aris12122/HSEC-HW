#pragma once

#include <string_view>
#include <vector>

class SearchEngine {
private:
    std::vector<std::string_view> lines_;
    std::vector<std::vector<std::string_view>> parsed_text_;
    
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;
};
