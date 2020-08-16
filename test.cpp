//
// Test the Landing game.
//
#include <iostream>
#include "landing.h"
#include "interact.h"
#include "catch/catch.hpp"

//
// Return the first n characters of a string.
//
std::string first_n(std::string &str, unsigned n)
{
    if (n == 0)
        return "";

    unsigned len = str.size();
    if (n >= len)
        return str;

    return str.substr(0, n);
}

//
// Return the last n characters of a string.
//
std::string last_n(std::string &str, unsigned n)
{
    if (n == 0)
        return "";

    unsigned len = str.size();
    if (n >= len)
        return str;

    return str.substr(len - n);
}

void check_and_send(Interact &session, const std::string &first, const std::string &last, const std::string &send)
{
    auto reply = session.receive();

    if (first.size() > 0)
        REQUIRE(first_n(reply, first.size()) == first);

    if (last.size() > 0)
        REQUIRE(last_n(reply, last.size()) == last);

    // Debug output: uncomment to see the landing progress.
    //std::cout << reply << send << std::endl;

    session.send(send);
}

//
// Check levels 2-9, same procedure.
//
TEST_CASE("level2", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "2\n");
    check_and_send(session, "", "RATE= ", "tv0\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "t:0\n");
    check_and_send(session, "", "RATE= ", "149\n");
    check_and_send(session, "", "RATE= ", "20\n");

    check_and_send(session, "ON THE MOON AT 163 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 443 LBS.", "", "");
}

TEST_CASE("level3", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "3\n");
    check_and_send(session, "", "RATE= ", "tv0\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "t:0\n");
    check_and_send(session, "", "RATE= ", "149\n");
    check_and_send(session, "", "RATE= ", "20\n");

    check_and_send(session, "ON THE MOON AT 163 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 943 LBS.", "", "");
}

TEST_CASE("level4", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "4\n");
    check_and_send(session, "", "RATE= ", "tv0\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "t:0\n");
    check_and_send(session, "", "RATE= ", "149\n");
    check_and_send(session, "", "RATE= ", "20\n");

    check_and_send(session, "ON THE MOON AT 163 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 1443 LBS.", "", "");
}

TEST_CASE("level5", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "5\n");
    check_and_send(session, "", "RATE= ", "tv0\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "t:0\n");
    check_and_send(session, "", "RATE= ", "149\n");
    check_and_send(session, "", "RATE= ", "20\n");

    check_and_send(session, "ON THE MOON AT 163 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 1943 LBS.", "", "");
}

TEST_CASE("level6", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "6\n");
    check_and_send(session, "", "RATE= ", "tv0\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "t:0\n");
    check_and_send(session, "", "RATE= ", "149\n");
    check_and_send(session, "", "RATE= ", "20\n");

    check_and_send(session, "ON THE MOON AT 163 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 2443 LBS.", "", "");
}

TEST_CASE("level7", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "7\n");
    check_and_send(session, "", "RATE= ", "tv0\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "t:0\n");
    check_and_send(session, "", "RATE= ", "149\n");
    check_and_send(session, "", "RATE= ", "20\n");

    check_and_send(session, "ON THE MOON AT 163 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 2943 LBS.", "", "");
}

TEST_CASE("level8", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "8\n");
    check_and_send(session, "", "RATE= ", "tv0\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "t:0\n");
    check_and_send(session, "", "RATE= ", "149\n");
    check_and_send(session, "", "RATE= ", "20\n");

    check_and_send(session, "ON THE MOON AT 163 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 3443 LBS.", "", "");
}

TEST_CASE("level9", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "9\n");
    check_and_send(session, "", "RATE= ", "tv0\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "t:0\n");
    check_and_send(session, "", "RATE= ", "149\n");
    check_and_send(session, "", "RATE= ", "20\n");

    check_and_send(session, "ON THE MOON AT 163 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 3943 LBS.", "", "");
}

//
// Check level 1: a few different procedures.
//
TEST_CASE("level1_residual0", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "1\n");
    check_and_send(session, "", "RATE= ", "tt0\n");
    check_and_send(session, "", "RATE= ", "t@200\n");
    check_and_send(session, "", "RATE= ", "t40\n");
    check_and_send(session, "", "RATE= ", "tl200\n");
    check_and_send(session, "", "RATE= ", "t414\n");
    check_and_send(session, "", "RATE= ", "59\n");
    check_and_send(session, "", "RATE= ", "8\n");

    check_and_send(session, "FUEL OUT AT 157 SECONDS.\n"
                            "ON THE MOON AT 157 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 0 LBS.", "", "");
}

TEST_CASE("level1_residual40", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "1\n");
    check_and_send(session, "", "RATE= ", "tu0\n");
    check_and_send(session, "", "RATE= ", "tE200\n");
    check_and_send(session, "", "RATE= ", "t30\n");
    check_and_send(session, "", "RATE= ", "tf200\n");
    check_and_send(session, "", "RATE= ", "t340\n");
    check_and_send(session, "", "RATE= ", "113\n");
    check_and_send(session, "", "RATE= ", "9\n");

    check_and_send(session, "ON THE MOON AT 153 SECONDS.\n"
                            "IMPACT VELOCITY OF 3 F.P.S.\n"
                            "FUEL LEFT 40 LBS.", "", "");
}

TEST_CASE("level1_residual51", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "1\n");
    check_and_send(session, "", "RATE= ", "tw0\n");
    check_and_send(session, "", "RATE= ", "tp200\n");
    check_and_send(session, "", "RATE= ", "t20\n");
    check_and_send(session, "", "RATE= ", "t<200\n");
    check_and_send(session, "", "RATE= ", "t2111\n");
    check_and_send(session, "", "RATE= ", "38\n");

    check_and_send(session, "ON THE MOON AT 152 SECONDS.\n"
                            "IMPACT VELOCITY OF 2 F.P.S.\n"
                            "FUEL LEFT 51 LBS.", "", "");
}

//
// Check level 0: out of fuel.
//
TEST_CASE("level0", "[landing]")
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "0\n");
    check_and_send(session, "", "RATE= ", "t{200\n");
    check_and_send(session, "FUEL OUT AT 75 SECONDS.\n"
                            "ON THE MOON AT 505 SECONDS.\n"
                            "IMPACT VELOCITY OF 2110 F.P.S.\n"
                            "FUEL LEFT 0 LBS.\n"
                            "THERE'S NOW A NEW LUNAR CRATER 400 FEET DEEP.\n", "", "");
}
