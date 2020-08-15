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

    std::cout << reply << send << std::endl;

    session.send(send);
}

//
// Check a few cases.
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

    check_and_send(session, "ON THE MOON", "", "");
}
