#include <cctype>
#include <cmath>
#include "search.h"

const double EPS = 1e-9;

std::vector<std::string_view> ParseLine(const std::string_view& line) {
    std::vector<std::string_view> parsed_line;
    const char* word_begin = std::find_if(line.begin(), line.end(), std::isalpha);
    while (word_begin != line.end()) {
        const char* word_end = std::find_if_not(word_begin, line.end(), std::isalpha);
        parsed_line.emplace_back(line.substr(word_begin - line.begin(), word_end - word_begin));
        word_begin = std::find_if(word_end, line.end(), std::isalpha);
    }
    return parsed_line;
}

std::vector<std::string_view> ParseText(const std::string_view& text) {
    std::vector<std::string_view> lines;
    const char* line_end = std::prev(text.begin());
    do {
        const char* line_begin = std::next(line_end);
        line_end = std::find(line_begin, text.end(), '\n');
        if (std::find_if(line_begin, line_end, std::isalpha) != line_end) {
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

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> lines = ParseText(text);
    std::vector<std::vector<std::string_view>> parsed_text = ParseLines(lines);
    std::vector<std::string_view> queries = ParseLine(query);

    std::size_t lines_number = parsed_text.size();

    std::vector<std::vector<std::size_t>> occurrence(lines_number, std::vector<std::size_t>(queries.size()));
    std::vector<std::size_t> cnt_in_text(queries.size());

    for (std::size_t line_num = 0; line_num < lines_number; ++line_num) {
        const auto& line = parsed_text[line_num];
        for (std::size_t word_num = 0; word_num < queries.size(); ++word_num) {
            const auto& word = queries[word_num];
            std::size_t cnt = static_cast<std::size_t>(count(line.begin(), line.end(), word));
            occurrence[line_num][word_num] = cnt;
            cnt_in_text[word_num] += cnt;
        }
    }

    std::vector<std::pair<double, std::size_t>> idf_line_num(lines_number);

    for (std::size_t line_num = 0; line_num < lines_number; ++line_num) {
        const auto& line = parsed_text[line_num];
        idf_line_num[line_num].second = line_num;
        for (std::size_t word_num = 0; word_num < queries.size(); ++word_num) {
            if (cnt_in_text[word_num] == 0) {
                continue;
            }
            idf_line_num[line_num].first += log(static_cast<double>(lines_number) / static_cast<double>(cnt_in_text[word_num])) *
                                            static_cast<double>(occurrence[line_num][word_num]) / static_cast<double>(line.size());
        }
    }

    std::stable_sort(idf_line_num.begin(), idf_line_num.end(),
                     [](const auto& idf1, const auto& idf2) { return idf1.first > idf2.first + EPS; });

    std::vector<std::string_view> most_relevant;

    for (std::size_t i = 0; i < std::min(results_count, lines_number); ++i) {
        const auto& [idf, line_num] = idf_line_num[i];
        if (idf > EPS) {
            most_relevant.emplace_back(lines[line_num]);
        }
    }
    return most_relevant;
}
