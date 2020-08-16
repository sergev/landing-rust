//! Translation of
//! <http://www.cs.brandeis.edu/~storer/LunarLander/LunarLander/LunarLanderListing.jpg>
//! by Jim Storer from FOCAL to Rust.

use std::error::Error;
use std::io;
use std::io::prelude::*;
use std::marker::{Send, Sync};
use std::process;
use std::str::FromStr;

fn main() {
    #![allow(clippy::cyclomatic_complexity)]
    #![allow(non_snake_case)]

    // Change this to "0_f64" to use double-precision floats
    let Zero = 0_f32;

    let mut A = Zero;
    let mut G = Zero;
    let mut I = Zero;
    let mut J = Zero;
    let mut K = Zero;
    let mut L = Zero;
    let mut M = Zero;
    let mut N = Zero;
    let mut S = Zero;
    let mut T = Zero;
    let mut V = Zero;
    let mut Z = Zero;

    // The loop below is a state machine that allows us to implement the
    // spaghetti control flow of the FOCAL code in Rust.  Each arm of the match
    // is a possible destination of a jump.  `next_location` is the next line
    // number in the FOCAL source to be executed.  `return_stack` is a
    // subroutine return stack.

    let mut next_location = 104;
    let mut return_stack: Vec<i32> = Vec::new();

    macro_rules! goto {
        ($location:expr) => {
            next_location = $location;
        };
    }
    macro_rules! call_subroutine {
        ($sub_location:expr, $return_location:expr) => {
            next_location = $sub_location;
            return_stack.push($return_location);
        };
    }
    macro_rules! return_from_subroutine {
        () => {
            next_location = return_stack.pop().unwrap();
        };
    }

    loop {
        match &mut next_location {
            104 => {
                println!(
                    "CONTROL CALLING LUNAR MODULE. MANUAL CONTROL IS NECESSARY
YOU MAY RESET FUEL RATE K EACH 10 SECS TO 0 OR ANY VALUE
BETWEEN 8 & 200 LBS/SEC. YOU'VE 16000 LBS FUEL. ESTIMATED
FREE FALL IMPACT TIME-120 SECS. CAPSULE WEIGHT-32500 LBS

"
                );
                goto!(120);
            }
            120 => {
                println!(
                    "FIRST RADAR CHECK COMING UP


COMMENCE LANDING PROCEDURE
TIME,SECS   ALTITUDE,MILES+FEET   VELOCITY,MPG   FUEL,LBS   FUEL RATE
"
                );
                A = 120.0;
                V = 1.0;
                M = 32500.0;
                N = 16500.0;
                G = 0.001;
                Z = 1.8;
                L = 0.0;
                goto!(210);
            }
            210 => {
                print!(
                    "{:7.0}{:16.0}{:7.0}{:15.2}{:12.1}      ",
                    L.round(),
                    A.trunc(),
                    (5280.0 * (A - A.trunc())).trunc(),
                    3600.0 * V,
                    M - N
                );
                goto!(211);
            }
            211 => {
                print!("K=:");
                match accept_value() {
                    Ok(num) => {
                        K = num;
                        T = 10.0;
                        goto!(270);
                    }
                    Err(err) => match err.kind() {
                        io::ErrorKind::InvalidData => goto!(272),
                        io::ErrorKind::UnexpectedEof => {
                            process::exit(-1);
                        }
                        _ => panic!("unable to read input"),
                    },
                }
            }
            270 => {
                if (200.0 - K) < 0.0 {
                    goto!(272);
                } else if (8.0 - K) <= 0.0 {
                    goto!(310);
                } else if K < 0.0 {
                    goto!(272);
                } else if K == 0.0 {
                    goto!(310);
                } else {
                    goto!(272);
                }
            }
            272 => {
                print!("NOT POSSIBLE");
                for _ in 1..=51 {
                    print!(".")
                }
                goto!(211);
            }
            310 => {
                if (M - N - 0.001) < 0.0 {
                    goto!(410);
                } else if (T - 0.001) < 0.0 {
                    goto!(210);
                } else {
                    S = T;
                    if (N + S * K - M) <= 0.0 {
                        goto!(350);
                    } else {
                        S = (M - N) / K;
                        goto!(350);
                    }
                }
            }
            350 => {
                call_subroutine!(910, 351);
            }
            351 => {
                if I <= 0.0 {
                    goto!(710);
                } else if V <= 0.0 {
                    goto!(380);
                } else if J < 0.0 {
                    goto!(810);
                } else {
                    goto!(380);
                }
            }
            380 => {
                call_subroutine!(610, 310);
            }
            410 => {
                println!("FUEL OUT AT {:8.2} SECS", L);
                S = ((V * V + 2.0 * A * G).sqrt() - V) / G;
                V += G * S;
                L += S;
                goto!(510)
            }
            510 => {
                println!("ON THE MOON AT {:8.2} SECS", L);
                let W = 3600.0 * V;
                println!("IMPACT VELOCITY OF {:8.2} M.P.H.", W);
                println!("FUEL LEFT: {:8.2} LBS", M - N);
                if W <= 1.0 {
                    println!("PERFECT LANDING !-(LUCKY)");
                } else if W <= 10.0 {
                    println!("GOOD LANDING-(COULD BE BETTER");
                } else if W <= 22.0 {
                    println!("CONGRATULATIONS ON A POOR LANDING");
                } else if W <= 40.0 {
                    println!("CRAFT DAMAGE. GOOD LUCK");
                } else if W <= 60.0 {
                    println!("CRASH LANDING-YOU'VE 5 HRS OXYGEN");
                } else {
                    println!("SORRY,BUT THERE WERE NO SURVIVORS-YOU BLEW IT!");
                    println!(
                        "IN FACT YOU BLASTED A NEW LUNAR CRATER {:8.2} FT. DEEP",
                        W * 0.277_777
                    );
                }
                println!("\n\n\n\nTRY AGAIN?");
                goto!(592);
            }
            592 => {
                print!("(ANS. YES OR NO):");
                match accept_line() {
                    Ok(line) => {
                        let line = line.trim().to_ascii_uppercase();
                        if line.starts_with('Y') {
                            goto!(120);
                        } else if line.starts_with('N') {
                            goto!(598);
                        } else {
                            goto!(592);
                        }
                    }
                    Err(_) => goto!(598),
                }
            }
            598 => {
                println!("CONTROL OUT\n\n");
                break;
            }
            610 => {
                L += S;
                T -= S;
                M -= S * K;
                A = I;
                V = J;
                return_from_subroutine!();
            }
            710 => {
                if (S - 0.005) < 0.0 {
                    goto!(510);
                } else {
                    S = 2.0 * A / (V + (V * V + 2.0 * A * (G - Z * K / M)).sqrt());
                    call_subroutine!(910, 730);
                }
            }
            730 => {
                call_subroutine!(610, 710);
            }
            810 => {
                let W = (1.0 - (M * G) / (Z * K)) / 2.0;
                S = M * V / (Z * K * (W + (W * W + V / Z).sqrt())) + 0.05;
                call_subroutine!(910, 830);
            }
            830 => {
                if I <= 0.0 {
                    goto!(710);
                } else {
                    call_subroutine!(610, 831);
                }
            }
            831 => {
                if -J <= 0.0 || V <= 0.0 {
                    goto!(310);
                } else {
                    goto!(810);
                }
            }
            910 => {
                let Q = S * K / M;
                J = V
                    + G * S
                    + Z * (-Q
                        - Q.powi(2) / 2.0
                        - Q.powi(3) / 3.0
                        - Q.powi(4) / 4.0
                        - Q.powi(5) / 5.0);
                I = A - G * S * S / 2.0 - V * S
                    + Z * S
                        * (Q / 2.0
                            + Q.powi(2) / 6.0
                            + Q.powi(3) / 12.0
                            + Q.powi(4) / 20.0
                            + Q.powi(5) / 30.0);
                return_from_subroutine!();
            }
            line_number => {
                panic!("destination {} does not exist", line_number);
            }
        }
    }
}

/// Reads a numeric value from standard input.
///
/// The value type `T` is expected to be something like `f32` or `f64`, but it
/// could be any type for which `str.parse()` is valid.
///
/// Returns an error with kind `std::io::ErrorKind::InvalidData` if text is read
/// that cannot be parsed as a numeric value.
///
/// Returns an error with kind `std::io::ErrorKind::UnexpectedEof` if
/// end-of-file is encountered without any preceding input.
fn accept_value<T>() -> io::Result<T>
where
    T: FromStr,
    <T as FromStr>::Err: 'static + Error + Send + Sync,
{
    let line = accept_line()?;
    if line.is_empty() {
        return Err(io::Error::new(io::ErrorKind::UnexpectedEof, "end of file"));
    }
    match line.trim().parse() {
        Ok(num) => Ok(num),
        Err(err) => Err(io::Error::new(io::ErrorKind::InvalidData, err)),
    }
}

/// Flushes standard output and reads a line from standard input.
///
/// On EOF, returns an empty string.
fn accept_line() -> io::Result<String> {
    io::stdout().flush()?;
    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    Ok(line)
}
