//
// Compute an optimal landing control sequence.
//
#include <iostream>
#include <iomanip>
#include "landing.h"
#include "interact.h"
#include "catch/catch.hpp"

static std::string reply;
static int initial_weight_lbs;
static int initial_fuel_lbs;

static int time_sec;
static int altitude_feet;
static int velocity_fps;
static int fuel_lbs;
static int prev_time_sec;
static int prev_altitude_feet;
static int prev_velocity_fps;
static int prev_fuel_lbs;

static const int FEET_PER_MILE = 5280;

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
void check_reply(const std::string &first, const std::string &last)
{
    if (first.size() > 0 &&
        first_n(reply, first.size()) != first)
        throw std::runtime_error("Wrong output, expect: " + first);

    if (last.size() > 0 &&
        last_n(reply, last.size()) != last)
        throw std::runtime_error("Wrong prompt, expect: " + last);
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

    reply = session.receive();
    check_reply(first, last);
}

//
// Somewhere in the string is located a number with a preceeding text.
// Find and return the number.
//
int fetch_value(std::string &str, const std::string &text)
{
    auto pos = str.find(text);
    assert(pos != std::string::npos);

    auto value = str.substr(pos + text.size());
    return std::stoi(value);
}

//
// From the last reply, extract values of initial weight and fuel supply.
//
void capture_weight_and_fuel()
{
    initial_weight_lbs = fetch_value(reply, "WEIGHT IS NOW");
    initial_fuel_lbs = fetch_value(reply, "YOU HAVE");
}

//
// Extract values of time, altitude, velocity and fuel.
//
//    0          120       0     5280        16000
//
void capture_state(std::string str)
{
    // Save previous state.
    prev_time_sec = time_sec;
    prev_altitude_feet = altitude_feet;
    prev_velocity_fps = velocity_fps;
    prev_fuel_lbs = fuel_lbs;

    // Scan the line.
    std::stringstream input (str);
    int miles, feet;
    input >> time_sec >> miles >> feet >> velocity_fps >> fuel_lbs;
    assert(!!input);

    // Convert miles into feet.
    altitude_feet = miles * FEET_PER_MILE + feet;
}

//
// From the last reply, extract values of time, altitude, velocity and fuel.
//
// TIME(SEC) ALT(MILES + FEET) VELOCITY(FPS) FUEL(LBS)
//    0          120       0     5280        16000
//
void capture_state0()
{
    std::string text = "VELOCITY(FPS) FUEL(LBS)";
    auto pos = reply.find(text);
    assert(pos != std::string::npos);

    capture_state(reply.substr(pos + text.size()));
}

//
// Level 2.
//
TEST_CASE("level2", "[landing]")
{
    Interact session(game);

    //-------------------------
    // Select level 2.
    //
    reply = session.receive();
    check_reply("MISSION CONTROL", "YOURS ? ");
    send_and_check(session, "2\n", "YOU MUST SPECIFY", "RATE= ");

    // Get initial weight and fuel supply.
    capture_weight_and_fuel();
    REQUIRE(initial_weight_lbs != 0);
    REQUIRE(initial_fuel_lbs != 0);
    std::cout << "Initial weight, lbs: " << initial_weight_lbs << "\n";
    std::cout << "Initial fuel, lbs: " << initial_fuel_lbs << "\n";

    // Get initial altitude and velocity.
    capture_state0();
    REQUIRE(time_sec == 0);
    REQUIRE(altitude_feet > 0);
    REQUIRE(velocity_fps > 0);
    REQUIRE(fuel_lbs == initial_fuel_lbs);
    std::cout << "Altitude, feet: " << altitude_feet << "\n";
    std::cout << "Velocity, fps: " << velocity_fps << "\n";

    //-------------------------
    // Free fall for 10 second.
    //
    std::string prompt = "RATE= ";
    send_and_check(session, "0\n", " ", prompt);

    // Measure gravity.
    capture_state(reply);
    REQUIRE(time_sec == 10);
    REQUIRE(altitude_feet < prev_altitude_feet);
    REQUIRE(velocity_fps > prev_velocity_fps);
    REQUIRE(fuel_lbs == prev_fuel_lbs);

    double gravity_fpss = (velocity_fps - prev_velocity_fps) / 10.0;
    std::cout << std::fixed << std::setprecision(1) << "Gravity, fpss: " << gravity_fpss << "\n";

    //-------------------------
    // Full thrust for 10 second.
    //
    send_and_check(session, "200\n", " ", prompt);

    // Measure thrust.
    capture_state(reply);
    REQUIRE(time_sec == 10 + prev_time_sec);
    REQUIRE(altitude_feet < prev_altitude_feet);
    REQUIRE(velocity_fps < prev_velocity_fps);
    REQUIRE(fuel_lbs < prev_fuel_lbs);

    int weight_lbs = initial_weight_lbs - initial_fuel_lbs + prev_fuel_lbs; // or current fuel_lbs?
    double thrust_fps = ((prev_velocity_fps - velocity_fps) / 10.0 + gravity_fpss) * weight_lbs / 200;
    std::cout << std::fixed << std::setprecision(0) << "Thrust, fps: " << thrust_fps << "\n";

    //
    // Compute optimal thrust.
    //
    for (;;) {
        int control = 72;

std::cout << reply << control << "\n";
        session.send(std::to_string(control) + "\n");
        reply = session.receive();

        if (last_n(reply, prompt.size()) != prompt)
            break;

        check_reply(" ", prompt);
    }
    std::cout << reply << std::endl;
}
