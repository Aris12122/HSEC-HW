#include <catch.hpp>
#include <password.h>

TEST_CASE("ValidatePassword") {
    REQUIRE(!ValidatePassword(""));
    REQUIRE(!ValidatePassword("!@"));
    REQUIRE(!ValidatePassword("!b@"));
    REQUIRE(!ValidatePassword("1!2@"));

    REQUIRE(!ValidatePassword("qwerty"));

    REQUIRE(ValidatePassword("Aa1!Bb2@"));
    REQUIRE(ValidatePassword("A1!B@AAA"));
    REQUIRE(ValidatePassword("1!b2@1111"));
    REQUIRE(ValidatePassword("Aa!Aa!Aa!"));
}
