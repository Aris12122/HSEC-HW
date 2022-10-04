#include <catch.hpp>

#include "zip.h"

#include <sstream>

TEST_CASE("Zip") {
    const std::forward_list<Value> a = {"1", "2", "3", "4"};
    const std::forward_list<Value> b = {"one", "two", "three"};
    std::stringstream stream;

    Zipped zipped = Zip(a.begin(), a.end(), b.begin(), b.end());
    for (auto it = zipped.begin(); it != zipped.end(); ++it) {
        const auto& pair = *it;
        stream << pair.first << ":" << pair.second << " ";
    }

    REQUIRE("1:one 2:two 3:three " == stream.str());
}
