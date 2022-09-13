#include <catch.hpp>
#include <password.h>

TEST_CASE("ValidatePassword") {
    REQUIRE(!ValidatePassword(""));
    REQUIRE(!ValidatePassword("!@"));
    REQUIRE(!ValidatePassword("!b@"));
    REQUIRE(!ValidatePassword("1!2@"));
    REQUIRE(!ValidatePassword("        "));
    REQUIRE(!ValidatePassword("11111111"));
    REQUIRE(!ValidatePassword("aaaaaaaa"));
    REQUIRE(!ValidatePassword("AAAAAAAA"));
    REQUIRE(!ValidatePassword("11aaAA1"));
    REQUIRE(ValidatePassword("!a21A12a!"));
    REQUIRE(ValidatePassword("111111111111Aa"));
    REQUIRE(!ValidatePassword("111111111111Aa1"));


    REQUIRE(!ValidatePassword("qwerty"));

    REQUIRE(ValidatePassword("Aa1!Bb2@"));
    REQUIRE(ValidatePassword("A1!B@AAA"));
    REQUIRE(ValidatePassword("1!b2@1111"));
    REQUIRE(ValidatePassword("Aa!Aa!Aa!"));
}
