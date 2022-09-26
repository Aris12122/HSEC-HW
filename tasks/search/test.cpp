#include <catch.hpp>

#include "search.h"

namespace {

bool Belongs(std::string_view text, std::string_view result) {
    return (result.data() >= text.data()) && (result.data() < (text.data() + text.size()));
}

}  // namespace

TEST_CASE("Search") {
    std::string_view text =
        ""
        "ab ba cd ab"
        " c vd bf\n"
        "cds"
        "\n";

    std::string_view query = "ab";
    std::vector<std::string_view> expected = {"electronic typesetting, remaining essentially"};

    const auto& actual = Search(text, query, 1);

    REQUIRE(expected == actual);
    SECTION("Result can not use extra memory") {
        for (const auto& doc : actual) {
            REQUIRE(Belongs(text, doc));
        }
    }
}
