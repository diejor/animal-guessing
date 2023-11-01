/* 
 * =====================================================================================
 *  Author: Diego R.R.
 *  Course: CS2337.501
 *  Description: 
 *      - This header file contains global constants and functions used throughout the 
 *        program.
 *      - To enable debugging tools, simply set the appropriate flag inside the 
 *        `debug_flags` namespace to `true`.
 *
 *  Changelog:
 *  -------------------------------------------------------------------------------------
 *      Date        |               Changes
 *  -------------------------------------------------------------------------------------
 *  10/29/2023     | Changed to implement animal guessing homework.
 *  10/30/2023     | Added debug flags.
 *  10/31/2023     | trim_whitespace fixed to handle empty strings.
 *  =====================================================================================
 */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

namespace global {
    // -----------------------------------------------
    // =----------------- CONSTANTS -----------------=
    namespace msgs {
        const string PROGRAM_TITLE =
            "    _          _                 _    ____                     _             \n"
            "   / \\   _ __ (_)_ __ ___   __ _| |  / ___|_   _  ___  ___ ___(_)_ __   __ _ \n"
            "  / _ \\ | '_ \\| | '_ ` _ \\ / _` | | | |  _| | | |/ _ \\/ __/ __| | '_ \\ / _` |\n"
            " / ___ \\| | | | | | | | | | (_| | | | |_| | |_| |  __/\\__ \\__ \\ | | | | (_| |\n"
            "/_/___\\_\\_| |_|_|_| |_| |_|\\__,_|_|  \\____|\\__,_|\\___||___/___/_|_| |_|\\__, |\n"
            " / ___| __ _ _ __ ___   ___                                             \\___/ \n"
            "| |  _ / _` | '_ ` _ \\ / _ \\                                                 \n"
            "| |_| | (_| | | | | | |  __/                                                 \n"
            " \\____|\\__,_|_| |_| |_|\\___|                                                 \n";

        const string INIT_GAME = R"(
            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    Welcome to the Animal Guess Game!         
            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            In this game, I will become an investigator to guess 
            the animal you are thinking of by asking you questions. 
            All you need to do is answer my questions with a 'y' 
            for yes or 'n' for no. Certainly if I can't guess the 
            correct animal, then I will learn from my mistakes! 
            By the end, I'll become smarter and better at this game 
            and maybe conquest the world.

            Are you ready to challenge me? Let the game begin!)";

        const string GOODBYE = R"(
            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        ¡Adiós vaquero!         
            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        )";

        // game loop
        const string DECISION = "Gimme a choice to initialize the decision tree";

        // user input
        const string INPUT_FILE_PATH = "Enter the path to the database file: ";
        const string OUTPUT_FILE_PATH = "Enter the path to the output file: ";
        const string ENTER_FILE_NAME = "Enter the file name: ";
        const string ENTER_FILE_NAME_AGAIN = "Enter the file name again: ";


    }  // namespace msgs

    namespace debug_flags {
        const bool stop_flow = false;
/* 
 * =====================================================================================
 *  Author: Diego R.R.
 *  Course: CS2337.501
 *  Description: 
 *      - This header file contains global constants and functions used throughout the 
 *        program.
 *      - To enable debugging tools, simply set the appropriate flag inside the 
 *        `debug_flags` namespace to `true`.
 *
 *  Changelog:
 *  -------------------------------------------------------------------------------------
 *      Date        |               Changes
 *  -------------------------------------------------------------------------------------
 *  10/29/2023     | Changed to implement animal guessing homework.
 *  10/30/2023     | Added debug flags.
 *  10/31/2023     | trim_whitespace fixed to handle empty strings.
 *  =====================================================================================
 */
        // main
        const bool INIT_VECTOR = false;
        const bool INIT_VECTOR_ADDING = false;

        // user input
        const bool TRIM_WHITESPACE = false;
        const bool USER_INPUT = false;

        // parser
        const bool EMPTY_FILE = false;
        const bool IGNORING_COMMENT_LINE = false;
        const bool TOKEN_LINE = false;

        // data
        const bool NODE_CREATED = false;

        // guessing
        const bool INSPECTING_NODE = false;
        const bool FLIPPING = false;

        // printing
        const bool PRINT_STEP = false;

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
            inline void stop_flow(const string& fnc) {
                if (debug_flags::stop_flow) {
                    string msg =
                        "stopping flow from " + fnc + ", please enter a key to continue ...";
                    cout << "DEBUG: " << msg << endl;
                    cin.get();
                    cin.ignore(100, '\n');
                }
            }

            inline void trim_whitespace(const string& input_file_name, int first_whspace_idx,
                                        int last_whspace_idx, string trimmed_input_file_name) {
                if (debug_flags::TRIM_WHITESPACE) {
                    string msg = "trimming whitespace from \"" + input_file_name + "\"" +
                                 "\n\tfirst whitespace index: " + to_string(first_whspace_idx) +
                                 "\n\tlast whitespace index: " + to_string(last_whspace_idx) +
                                 "\n\ttrimmed string: \"" + trimmed_input_file_name + "\"";
                    cout << "DEBUG: " << msg << endl;
                }
            }
        }  // namespace debug
        
       /*
            Used to trim leading and trailing whitespaces from the user input.
        */
        inline string trim_whitespace(const string& str) {
            if (str.empty()) {
                return str;
            }
            unsigned int first = str.find_first_not_of(' ');
            unsigned int last = str.find_last_not_of(' ');
            string trimmed_str = str.substr(first, (last - first + 1));
            debug::trim_whitespace(str, first, last, trimmed_str);
            return trimmed_str;
        }

        inline string to_lower(const string& str) {
            string lower_case_str;
            for (char ch : str) {
                lower_case_str += tolower(ch);
            }
            return lower_case_str;
        }

        inline bool contains(const string& str, const string& regex) {
            string str_lower = to_lower(str);
            string regex_lower = to_lower(regex);
            return str_lower.find(regex_lower) != string::npos;
        }

    }  // namespace fncs
    // =----------------- END OF GLOBAL FUNCTIONS -----------------=
    // -------------------------------------------------------------

}  // namespace global

#endif  // GLOBAL_HPP
