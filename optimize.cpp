#include <iostream>
#include "landing.h"
#include "interact.h"

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

    if (first.size() > 0 &&
        first_n(reply, first.size()) != first)
        throw std::runtime_error("Wrong output, expect: " + first);

    if (last.size() > 0 &&
        last_n(reply, last.size()) != last)
        throw std::runtime_error("Wrong prompt, expect: " + last);

    // Debug output: uncomment to see the landing progress.
    std::cout << reply << send << std::endl;

    session.send(send);
}

int main()
{
    Interact session(game);
#if 0
    check_and_send(session, "", "YOURS ? ", "0\n");
    check_and_send(session, "", "RATE= ", "t1200\n");
    check_and_send(session, "", "RATE= ", "200\n");

    std::string prompt = "RATE= ";
    for (;;) {
        auto reply = session.receive();

        if (last_n(reply, prompt.size()) != prompt) {
            std::cout << reply << std::endl;
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
#endif
#if 0
    check_and_send(session, "", "YOURS ? ", "0\n");
    check_and_send(session, "", "RATE= ", "t1200\n");
    check_and_send(session, "", "RATE= ", "200\n");
    check_and_send(session, "", "RATE= ", "200\n");

    std::string prompt = "RATE= ";
    for (;;) {
        auto reply = session.receive();

        if (last_n(reply, prompt.size()) != prompt) {
            std::cout << reply << std::endl;
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
#endif
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
        auto reply = session.receive();

        if (last_n(reply, prompt.size()) != prompt) {
            std::cout << reply << std::endl;
            break;
        }

        std::string send = "27\n";
        std::cout << reply << send;

        session.send(send);
    }
    return 0;
}
