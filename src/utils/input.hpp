#ifndef INPUT_HPP
#define INPUT_HPP
/*
 * Input Handler
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
 *  10/29/2023 - changed to implement animal guessing homework, removed 
 *  integer_within_threasold function
 *
 * notes:
 */

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
        inline void user_input(const string& input) {
            if (global::debug_flags::USER_INPUT) {
                output::debug("user input =" + input);
            }
        }

    }  // namespace debug

    /*
     *   Used to retrieve a whole line of input from the user.
     */
    inline string line(const string& msg) {
        string input;
        output::ask_for_input(msg + " : ");
        getline(cin, input);

        if (input.empty()) {
            output::error("input is empty");
            return line(msg);
        }

        string no_whitespace = global::fncs::trim_whitespace(input);
        debug::user_input(no_whitespace);
        return no_whitespace;
    }

    inline int integer(const string& msg) {
        int input;
        output::ask_for_input(msg);
        while (!(cin >> input)) {
            output::error("invalid input");
            output::ask_for_input(msg + " (must be an integer)");
            cin.clear();  // Clear the error state.
            cin.ignore(100, '\n');  // Discard non-integer input.
        }
        cin.ignore(1, '\n');  // Discard the newline character.
        debug::user_input(to_string(input));
        return input;
    }

    inline int integer_within_range(const string& msg, int min, int max) {
        int input = integer(msg);
        while (input < min || input > max) {
            output::error("input must be between " + to_string(min) + " and " + to_string(max));
            input = integer(msg);
        }
        return input;
    }

    inline int select(const string& msg, const vector<string>& options) {
        output::select(msg, options);
        int input = integer_within_range("Enter your selection : ", 1, options.size());
        return input;
    }
}  // namespace input

#endif  // INPUT_HPP
