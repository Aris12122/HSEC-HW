#include <cctype>
#include <cmath>
#include <unordered_set>
#include <string>
#include "search.h"

const double EPS = 1e-8;

std::vector<std::string_view> ParseLine(const std::string_view& line) {
    std::vector<std::string_view> parsed_line;
    const char* word_begin = std::find_if(line.begin(), line.end(), isalpha);
    while (word_begin != line.end()) {
        const char* word_end = std::find_if_not(word_begin, line.end(), isalpha);
        parsed_line.emplace_back(line.substr(word_begin - line.begin(), word_end - word_begin));
        word_begin = std::find_if(word_end, line.end(), isalpha);
    }
    return parsed_line;
}

std::vector<std::string_view> ParseText(const std::string_view& text) {
    std::vector<std::string_view> lines;
    const char* line_end = std::prev(text.begin());
    do {
        const char* line_begin = std::next(line_end);
        line_end = std::find(line_begin, text.end(), '\n');
        if (std::find_if(line_begin, line_end, isalpha) != line_end) {
            lines.emplace_back(text.substr(line_begin - text.begin(), line_end - line_begin));
        }
    } while (line_end != text.end());
    return lines;
}

std::vector<std::vector<std::string_view>> ParseLines(const std::vector<std::string_view>& lines) {
    std::vector<std::vector<std::string_view>> parsed_text;
    for (const auto& line : lines) {
        parsed_text.emplace_back(ParseLine(line));
    }
    return parsed_text;
}

std::string ToLower(const std::string_view& str_v) {
    std::string str;
    for (std::size_t i = 0; i < str_v.size(); ++i) {
        str += static_cast<char>(std::tolower(static_cast<int>(str_v[i])));
    }
    return str;
}

void SearchEngine::BuildIndex(std::string_view text) {
    lines_ = ParseText(text);
    parsed_text_ = ParseLines(lines_);
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    std::vector<std::string_view> parsed_query = ParseLine(query);
    std::unordered_set<std::string_view> queries;

    for (const auto& str : parsed_query) {
        queries.insert(std::move(str));
    }

    std::size_t lines_number = parsed_text_.size();

    std::vector<std::vector<std::size_t>> occurrence(lines_number, std::vector<std::size_t>(queries.size()));
    std::vector<std::size_t> cnt_in_text(queries.size(), 0u);

    for (std::size_t line_num = 0; line_num < lines_number; ++line_num) {
        const auto& line = parsed_text_[line_num];
        std::size_t word_num = 0;
        for (const auto& word : queries) {
            std::size_t cnt = static_cast<std::size_t>(
                count_if(line.begin(), line.end(), [&](const std::string_view& str) { return ToLower(str) == word; }));

            occurrence[line_num][word_num] = cnt;
            if (cnt > 0) {
                ++cnt_in_text[word_num];
            }
            word_num++;
        }
    }

    std::vector<std::pair<double, std::size_t>> idf_line_num(lines_number);

    for (std::size_t line_num = 0; line_num < lines_number; ++line_num) {
        const auto& line = parsed_text_[line_num];
        idf_line_num[line_num] = {0., line_num};
        for (std::size_t word_num = 0; word_num < queries.size(); ++word_num) {
            if (cnt_in_text[word_num] == 0u) {
                continue;
            }
            idf_line_num[line_num].first +=
                log(static_cast<double>(lines_number) / static_cast<double>(cnt_in_text[word_num])) *
                static_cast<double>(occurrence[line_num][word_num]) / static_cast<double>(line.size());
        }
    }

    std::stable_sort(idf_line_num.begin(), idf_line_num.end(),
                     [](const auto& idf1, const auto& idf2) { return idf1.first > idf2.first + EPS; });

    std::vector<std::string_view> most_relevant;

    for (std::size_t i = 0; i < std::min(results_count, lines_number); ++i) {
        const auto& [idf, line_num] = idf_line_num[i];
        if (idf > EPS) {
            most_relevant.emplace_back(lines_[line_num]);
        }
    }
    return most_relevant;
}
