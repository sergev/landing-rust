#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <unistd.h>
#include "landing.h"

using std::setw;

int ruined, l2v45z, msgarg;
bool verbose;

void landMsg(int msg, std::ostream &cout) {
    switch (msg) {
    case 0:
        cout << "I UNDERSTOOD IT AS NIL.\n"; break;
    case 1:
        cout << "MISSION CONTROL OUT.\n"; break;
    case 2:
        cout << "YOU BLEW IT AGAIN. WELL, THIRD TIMES THE CHARM.....\n"; break;
    case 3:
        cout << "HOW DOES IT FEEL TO TASTE DEATH TREE TIMES....??\n"; break;
    case 4:
        cout << "NEXT TIME BRING ALONG YOUR BIBLE.\n"; break;
    case 5:
        cout << "DO NOT APPLY TO NASA FOR A JOB. YOU""LL NEVER MAKE IT.\n"; break;
    case 6:
        cout << "YOU""VE RUINED SIX MISSIONS NOW. TURN IN YOUR SPACESUIT.\n"; break;
    case 7:
        cout << ".......SPLAT.  NOT SO GOOD.  INEXPERIENCE PERHAPS.\n"; break;
    case 8:
        cout << "MISSION CONTROL CALLING LUNAR MODULE:\nMANUAL CONTROL IS NECESSARY FOR LANDING.\nWHAT IS YOUR EXPERIENCE: 0 1 2(STANDARD) 3 4 5 6 7 8 9(NO EXPERIENCE) ?\n"; break;
    case 9:
        cout << "YOU MUST SPECIFY A FUEL RATE EACH 10 SECONDS.\nRATES MUST BE ZERO OR BETWEEN 8 AND 200 LBS.PER SEC.\n"; break;
    case 10:
        cout << "YOU HAVE " << msgarg << " LBS OF FUEL.\nCAPSULE WEIGHT IS NOW 32500 LBS INCLUDING FUEL.\nCOMMENCE LANDING PROCED.\n"; break;
    case 11:
        cout << "FIRST RADAR CHECK COMING UP:\n TIME(SEC) ALT(MILES + FEET) VELOCITY(FPS) FUEL(LBS)\n"; break;
    case 12:
        cout << "DON'T WASTE TIME TRYING TO BURN AT THAT RATE.\n"; break;
      case 13:
          cout << "FUEL OUT AT " << msgarg << " SECONDS.\n"; break;
      case 14:
          cout << "ON THE MOON AT " << msgarg << " SECONDS.\n"; break;
      case 15:
          cout << "IMPACT VELOCITY OF " << msgarg << " F.P.S.\n"; break;
      case 16:
          cout << "FUEL LEFT " << msgarg << " LBS.\n"; break;
      case 17:
          cout << "PERFECT LANDING. YOU LUCKY JET JOCKEY.\n"; break;
      case 18:
          cout << "A GOOD LANDING, NOT GREAT, JUST GOOD.\n"; break;
      case 19:
          cout << "BUCK ROGERS YOUR NOT, BUT CONGRATULATIONS, YOU'RE DOWN.\n"; break;
      case 20:
          cout << "HEAVY CRAFT DAMAGE, YOU MAY NEVER SEE EARTH AGAIN.\n"; break;
      case 21:
          cout << "THERE'S NOW A NEW LUNAR CRATER " << msgarg << " FEET DEEP.\n"; break;
      case 22:
          cout << "PERFECT RECORD! NO FAIR USING CALCULATING AIDS.\n"; break;
      case 23:
          cout << "NASA WILL DEDUCT $" << msgarg << " FROM YOUR PAYCHECK EACH WEEK "; break;
      case 24:
          cout << "FOR THE L.E.M. YOU WIPED OUT.\n"; break;
      case 25:
          cout << "FOR THE " << msgarg << " L.E.M.""S YOU WIPED OUT.\n";
    }
}

struct LEMState {
  double Vfps, elapsed, altitude, Vmps, mass;
  double drymass, lunarG, impulse, remaining, newalt, newVmps, deltaT;
  double runout;
  int interval;

    bool getval(double &val, std::istream &cin, std::ostream &cout);
    void update(double rate) {
        elapsed = elapsed + deltaT;
        remaining = remaining - deltaT;
        mass = mass - deltaT * rate;
        altitude = newalt;
        Vmps = newVmps;
        Vfps = Vmps*5280;
    }
    void P4250(double rate) {
      double x = deltaT * rate / mass, x2 = x * x, x3 = x2 * x, x4 = x2 * x2, x5 = x4 * x;
        newVmps = (((lunarG * deltaT) + Vmps) - (log(1.0 + x) * impulse));
        // newVmps = (((lunarG * deltaT) + Vmps) + (log(1.0-x) * impulse));
        newalt = (((altitude - (((lunarG * deltaT) * deltaT) / (2.0))) - (Vmps * deltaT)) +
                  ((impulse * deltaT) * (((((x / (2.0)) + (x2 / (6.0))) +
                                          (x3 / (12.0))) + (x4 / (20.0))) + (x5 / (30.0)))));
    }
    void init(double fuel) {
        interval = 10;
        elapsed = 0;
        altitude = 120;
        Vmps = 1.0;
        mass = 32500;
        drymass = mass - fuel;
        lunarG = 1.0e-3;
        impulse = 1.8;
    }
    void report(std::ostream &cout) {
        cout << setw(5) << round(elapsed) << setw(13) << trunc(altitude) <<
            setw(8) << trunc((((altitude - (trunc(altitude))) * (5280)) + (0.5))) <<
            setw(9) << trunc((((5280) * Vmps) + (0.5))) <<
            setw(13) << round(((mass) - drymass));
        if (verbose)
            cout << ' ' << setw(0) << Vmps * Vmps / altitude;
        cout << '\n';
    }

    void landing(double fuel, std::istream &cin, std::ostream &cout);
    bool run1sec(double rate); // true = on the ground
    bool runinterval(int interval, double rate); // true = on the ground
};

LEMState cur, saved;

bool LEMState::getval(double & val, std::istream &cin, std::ostream &cout) {
    int l3v1z;
    std::string str;
    int i = 0;
    l3v1z = 0;

    if (cin.eof())
        return false;
    if (!std::getline(cin, str))
        return false;

    do {
        char c = str[i];
        switch (c) {
        case 'K': case 'k' : exit(0);
        case 'S': case 's': saved = cur; break;
        case 'T': case 't':
          interval = str[++i]-'0';
          ++i;
          continue;
        case 'Y': case 'y': verbose = 1; ++i; continue;
        case 'R': case 'r': cur = saved; break;
        }
        val = -1;
        while ('0' <= c && c <= '9') {
            val = 0;
            l3v1z = 10*l3v1z + c - '0';
            c = str[++i];
        }
        if (val == -1) {
            landMsg(0, cout);
        } else {
            val = l3v1z;
        }
        break;
    } while (true);

    return true;
}

void ending(std::ostream &cout) {
    landMsg(1, cout);
    exit(0);
}

void dead(std::ostream &cout) {
    if (ruined == 1)
        landMsg(7, cout); /* splat */
    else if (ruined < 6)
        landMsg(ruined, cout); /* oops again */
    else {
        landMsg(6, cout); /* enough already */
        ending(cout);
    }
}

bool LEMState::runinterval(int interval, double rate) {
    for (int cursec = 1; cursec <= interval; ++cursec) {
        if (run1sec(rate))
            return true;
    }
    return false;
}

void LEMState::landing(double fuel, std::istream &cin, std::ostream &cout) {
    std::string str;
    double input;
    verbose = false;
    l2v45z = 0;
    ruined = 0;
  L4354: {
        landMsg(11, cout);
        init(fuel);
        if (l2v45z == 0)
            saved = cur;
        else
            l2v45z = 1;
      L4410:
        report(cout);

        do {
            cout << "FUEL RATE= ";
            if (!getval(input, cin, cout))
                return;
            if (((input < 8.0) || (input > 200)) && (input != 0.0)) {
                landMsg(12, cout);
            }
        } while (((input < 8.0) || (input > 200)) && (input != 0.0));
        bool landed = runinterval(interval, input);
        if (mass - drymass < 1.0e-3) {
            // fuel out
            msgarg = round(runout);
            landMsg(13, cout);
        }
        if (!landed)
            goto L4410;
      //L4514:
        msgarg = round(elapsed);
        landMsg(14, cout); /* on the Moon at ... sec */
        Vfps = (5280 * Vmps);
        msgarg = round(Vfps);
        landMsg(15, cout); /* impact velocity */
        elapsed = mass - drymass;
        if (elapsed < 0.0)
            elapsed = 0.0;
        msgarg = round( elapsed );
        landMsg(16, cout); /* fuel remaining */
        if (Vfps <= 3) landMsg(17, cout); /* perfect */
        else if (Vfps <= 15) landMsg(18, cout); /* good */
        else if (Vfps <= 35) landMsg(19, cout); /* no Buck Rogers */
        else if (Vfps <= 80) landMsg(20, cout); /* heavy damage */
        else {
            msgarg = trunc(0.19 * Vfps);
            landMsg(21, cout); /* crater */
            ruined = ruined + 1;
            dead(cout);
        }
        do {
            cout << "TRY AGAIN (1) OR NOT (0) ? ";
            if (!std::getline(cin, str))
                return;
        } while (str[0] != '0' && str[0] != '1');
        if (str[0] != '0')
            goto L4354;
        if (ruined == 0)
            landMsg(22, cout);
        else {
            msgarg = round(ruined * 34.23);
            landMsg(23, cout);
            msgarg = ruined;
            if (ruined == 1)
                landMsg(24, cout);
            else
                landMsg(25, cout);
        }
        ending(cout);

        goto L4410;
    } /* L4354 */
    ending(cout);
}

// Returns true at touchdown
bool
LEMState::run1sec(double rate) {
    remaining = 1.0;
  L4472: if (mass - drymass < 1.0e-3) {
        runout = elapsed;
        deltaT = ((-(Vmps) + sqrt(((Vmps * Vmps) + ((2 * altitude) * lunarG)))) / lunarG);
        Vmps = ((lunarG * deltaT) + Vmps);
        elapsed = (elapsed + deltaT);
        return true;
    } else if (remaining < (1.0e-3))
        return false;
    else {
        deltaT = remaining;
        if ((((deltaT) * rate) + drymass) > mass)
            deltaT = (((mass) - drymass) / rate);
        P4250(rate);
        if (newalt <= 0.0)
          L4636: {
                if (deltaT < 5.0e-3)
                    return true;
                deltaT = ((2.0 * altitude) /
                          (sqrt(((Vmps * Vmps) + ((2.0 * altitude) * (lunarG - (((impulse) * rate) / mass))))) + Vmps));
                P4250(rate);
                update(rate);
                goto L4636;
            }
        if (Vmps <= 0.0) {
            update(rate);
            goto L4472;
        }
        if (newVmps < 0.0)
          L4664: {
                Vfps = ((1.0 - ((mass * lunarG) / (impulse * rate))) / 2.0);
                deltaT = (((mass * Vmps) / ((impulse * rate) * (sqrt(((Vfps * Vfps) + (Vmps / impulse))) + Vfps))) + 0.05);
                P4250(rate);
                if (newalt <= 0.0)
                    goto L4636;
                update(rate);
                if ((-newVmps > 0.0) && (Vmps > 0.0)) {} else goto L4472;
                goto L4664;
            } else {
            update(rate);
            goto L4472;
        }
    }
}

void game(std::istream &cin, std::ostream &cout) {
    landMsg(8, cout);
    cout << "WHAT IS YOURS ? ";
    double input;
    if (!cur.getval(input, cin, cout))
        return;
    if (trunc(input) < 0 || trunc(input) > 9)
        input = 9.0;
    landMsg(9, cout);
    double fuel = round(15000 + input * 500);
    msgarg = fuel;
    landMsg(10, cout);
    cur.landing(fuel, cin, cout);
}
