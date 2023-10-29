/* 
 * CS2337.501
 *
 * Global constants and functions used throughout the program.
 *
 * Changelog:
 * - Added comments
 *
 * Notes:
 */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "output.hpp"

using namespace std;

namespace global {
    // -----------------------------------------------
    // =----------------- CONSTANTS -----------------=
    namespace msgs {
        const string WELCOME_MSG = "Welcome! ";
    }  // namespace msgs

    namespace debug_flags {
        const bool stop_flow = false;

        // main
        const bool INIT_VECTOR = false;
        const bool INIT_VECTOR_ADDING = false;

        // user input
        const bool TRIM_WHITESPACE = false;
        const bool USER_INPUT = false;

        // linked list
        const bool NODE_CREATION = false;
        const bool ADDING_NODE = false;
        const bool LINK_LIST_CONTENTS = false;

    }  // namespace debug_flags
    // =----------------- END OF CONSTANTS -----------------=
    // ------------------------------------------------------

    // ------------------------------------------------------
    // =----------------- GLOBAL FUNCTIONS -----------------=
    namespace fncs {

        /*
        *   Debug routines
        */
        namespace debug {
            void stop_flow(const string& fnc) {
                if (debug_flags::stop_flow) {
                    string msg = "stopping flow from " + fnc + ", please enter a key to continue ...";
                    output::debug(msg);
                    cin.get();
                    cin.ignore(100, '\n');
                }
            }

            void trim_whitespace(
                const string& input_file_name, int first_whspace_idx,
                int last_whspace_idx, string trimmed_input_file_name
            ) {
                if (debug_flags::TRIM_WHITESPACE) {
                    string msg = "trimming whitespace from \"" + input_file_name + "\""
                        + "\n\tfirst whitespace index: " + to_string(first_whspace_idx)
                        + "\n\tlast whitespace index: " + to_string(last_whspace_idx)
                        + "\n\ttrimmed string: \"" + trimmed_input_file_name + "\"";
                    output::debug(msg);
                }
            }
        }  // namespace debug

        void assert_in_bounds(int idx, int size) {
            if (idx < 0 || idx >= size) {
                string msg = "index " + to_string(idx) + " is out of bounds (size: " + to_string(size) + ")";
                output::error(msg);
                exit(1);
            }
        }

        /*
            Used to trim leading and trailing whitespaces from the user input.
        */
        string trim_whitespace(const string& str) {
            unsigned int first = str.find_first_not_of(' ');
            unsigned int last = str.find_last_not_of(' ');
            string trimmed_str = str.substr(first, (last - first + 1));
            debug::trim_whitespace(str, first, last, trimmed_str);
            return trimmed_str;
        }

        string to_lower(const string& str) {
            string lower_case_str;
            for (char ch : str) {
                lower_case_str += tolower(ch);
            }
            return lower_case_str;
        }

        bool contains(const string& str, const string& regex) {
            return str.find(regex) != string::npos;
        }

    }  // namespace fncs
    // =----------------- END OF GLOBAL FUNCTIONS -----------------=
    // -------------------------------------------------------------

}  // namespace global

#endif  // GLOBAL_HPP
