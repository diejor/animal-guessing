/*
 * title: Input Handler
 * file: input.hpp
 * author: Diego R.R.
 * started: 10/16/2023
 * course: CS2337.501
 *
 * functions used to retrieve input from user
 *
 * changelog:
 *  10/16/2023 - initial completion
 *  10/22/2023 - integer bug fixed when non-integer input is given
 *
 * notes:
 */

#ifndef INPUT_HPP
#define INPUT_HPP

#include <fstream>
#include <string>
#include <vector>

#include "global.hpp"
#include "output.hpp"

using namespace std;

namespace input {

    /*
     *  Debug routines
     */
    namespace debug {
        void user_input(const string& input) {
            if (global::debug_flags::USER_INPUT) {
                cout << "DEBUG: user input: " << input << endl;
            }
        }

    }  // namespace debug

    /*
     *   Used to retrieve a whole line of input from the user.
     */
    string line(const string& msg) {
        string input;
        output::ask_for_input(msg);
        getline(cin, input);
        string no_leading_preceding_whitespace = global::fncs::trim_whitespace(input);
        debug::user_input(no_leading_preceding_whitespace);
        return no_leading_preceding_whitespace;
    }

    int integer(const string& msg) {
        int input;
        output::ask_for_input(msg);
        while (!(cin >> input)) {
            output::error("invalid input");
            output::ask_for_input(msg + " (must be an integer)");
            cin.clear();  // Clear the error state.
            cin.ignore(100, '\n');  // Discard non-integer input.
        }
        debug::user_input(to_string(input));
        return input;
    }

    int integer_within_threshold(const string& msg, int threshold) {
        int input = integer(msg);
        while (!(input <= threshold)) {
            input = integer(msg + " (must be less than " + to_string(threshold + 1) + ")");
        }
        return input;
    }

}  // namespace input

#endif  // INPUT_HPP
