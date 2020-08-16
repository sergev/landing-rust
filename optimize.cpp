//
// Compute an optimal landing control sequence.
//
#include <iostream>
#include "landing.h"
#include "interact.h"
#include "catch/catch.hpp"

static std::string reply;
static int initial_weight; // lbs
static int initial_fuel;   // lbs

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

//
// Read reply.
// Rememer it as last_reply for later processing.
// Make sure the beginning of the reply matches `first' string.
// Make sure the tail of the reply matches `last' string.
//
void check_reply(Interact &session, const std::string &first, const std::string &last)
{
    reply = session.receive();

    if (first.size() > 0 &&
        first_n(reply, first.size()) != first)
        throw std::runtime_error("Wrong output, expect: " + first);

    if (last.size() > 0 &&
        last_n(reply, last.size()) != last)
        throw std::runtime_error("Wrong prompt, expect: " + last);
}

//
// Read reply.
// Rememer it as last_reply for later processing.
// Make sure the beginning of the reply matches `first' string.
// Make sure the tail of the reply matches `last' string.
// Send the `send' command.
//
void check_and_send(Interact &session, const std::string &first, const std::string &last, const std::string &send)
{
    check_reply(session, first, last);

    // Debug output.
    // Comment out this for less verbosity.
    std::cout << reply << send;

    session.send(send);
}

//
// Send the `send' command.
// Read reply.
// Rememer it as last_reply for later processing.
// Make sure the beginning of the reply matches `first' string.
// Make sure the tail of the reply matches `last' string.
//
void send_and_check(Interact &session, const std::string &send, const std::string &first, const std::string &last)
{
    // Comment out this for less verbosity.
    std::cout << reply << send;
    std::cout.flush();

    session.send(send);

    check_reply(session, first, last);
}

//
// From the last reply, extract values of initial weight and fuel supply.
//
void capture_weight_and_fuel()
{
    //TODO
}

void try1()
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "0\n");
    check_and_send(session, "", "RATE= ", "t1200\n");
    check_and_send(session, "", "RATE= ", "200\n");

    std::string prompt = "RATE= ";
    for (;;) {
        reply = session.receive();

        if (last_n(reply, prompt.size()) != prompt) {
            std::cout << reply;
            break;
        }

        std::string send = "73\n";
        std::cout << reply << send;

        session.send(send);
    }
    // FUEL OUT AT 202 SECONDS.
    // ON THE MOON AT 202 SECONDS.
    // IMPACT VELOCITY OF 482 F.P.S.
    // FUEL LEFT 0 LBS.
    // THERE'S NOW A NEW LUNAR CRATER 91 FEET DEEP.
}

void try2()
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "0\n");
    check_and_send(session, "", "RATE= ", "t1200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");

    std::string prompt = "RATE= ";
    for (;;) {
        reply = session.receive();

        if (last_n(reply, prompt.size()) != prompt) {
            std::cout << reply;
            break;
        }

        std::string send = "72\n";
        std::cout << reply << send;

        session.send(send);
    }
    // FUEL OUT AT 203 SECONDS.
    // ON THE MOON AT 205 SECONDS.
    // IMPACT VELOCITY OF 497 F.P.S.
    // FUEL LEFT 0 LBS.
    // THERE'S NOW A NEW LUNAR CRATER 94 FEET DEEP.
}

void try3()
{
    Interact session(game);

    check_and_send(session, "", "YOURS ? ", "1\n");
    check_and_send(session, "", "RATE= ", "t1200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");

    std::string prompt = "RATE= ";
    for (;;) {
        reply = session.receive();

        if (last_n(reply, prompt.size()) != prompt) {
            std::cout << reply;
            break;
        }

        std::string send = "27\n";
        std::cout << reply << send;

        session.send(send);
    }
}

//
// Level 2.
//
TEST_CASE("level2", "[landing]")
{
    Interact session(game);
    check_reply(session, "MISSION CONTROL", "YOURS ? ");

    send_and_check(session, "2\n", "", "RATE= ");
    capture_weight_and_fuel();
    REQUIRE(initial_weight != 0);
    REQUIRE(initial_fuel != 0);
}
