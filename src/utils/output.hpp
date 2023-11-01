/*
 * Output Management System
 * file: output.hpp
 * author: Diego R.R.
 * started: 10/16/2023
 * course: CS2337.501
 *
 * This header provides a collection of utility functions designed 
 * to handle the output operations for the program. Whether it's 
 * displaying error messages, debugging information, user prompts, 
 * or other informative content, this file centralizes those operations.
 * 
 * Purpose:
 * Centralizing output operations ensures consistency in how 
 * messages and information are displayed to the user and 
 * aids in maintaining a uniform look and feel.
 * 
 * changelog:
 *  10/29/2023 - Revisions made for the animal guessing homework. Removed the vector table display functions.
 *
 * Usage:
 * - For general messages: use the `inform` function.
 * - To prompt the user for input: use the `ask_for_input` function.
 * - For errors: there's the `error` for standard issues, and `error_nonexpected` for unforeseen problems.
 * - Debugging purposes: utilize the `debug` function(s).
 * - To display program flow messages (like greetings or endings), there are `welcome`, `init_game`, and `goodbye` functions.
 */

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "global.hpp"

using namespace std;

namespace output {

    // Prompt the user for input
    inline void ask_for_input(const string& msg) {
        cout << msg;
    }

    // Standard error messages
    inline void error(const string& msg) {
        cout << "ERROR: " << msg << endl;
    }

    // Unexpected error messages
    inline void error_nonexpected(const string& msg) {
        cout << "UNEXPECTED ERROR: " << msg << endl;
    }

    // Debug messages
    inline void debug(const string& msg) {
        cout << "DEBUG: " << msg << endl;
    }
    
    // Debug messages with an option
    inline void debug(const string& msg, const string& opt) {
        cout << "DEBUG: " << msg << opt << endl;
    }

    // To-do notices
    inline void toDO(const string& msg) {
        cout << "TO DO: " << msg << endl;
    }

    // Repeating a string multiple times
    inline void repeat(const string& str, int times) {
        for (int i = 0; i < times; i++) {
            cout << str;
        }
    }

    // Provides a separator line for readability
    inline void separate() {
        cout << endl;
    }

    // Display general informative messages to the user
    inline void inform(const string& msg) {
        cout << "  ~  " << msg << endl;
    }

    // Welcome message when the program starts
    inline void welcome() {
        cout << global::msgs::PROGRAM_TITLE << endl;
    }

    // Display a message when the game initializes
    inline void init_game() {
        cout << global::msgs::INIT_GAME << endl;
        separate();
    }

    // Goodbye message when the program ends
    inline void goodbye() {
        cout << global::msgs::GOODBYE << endl;
    }

    // Display options and prompt user to make a selection
    inline void select(const string& msg, const vector<string>& options) {
        cout << msg << " (select a number)" << endl;
        for (int i = 0; i < options.size(); i++) {
            cout << "\t" << i + 1 << ". " << options[i] << endl;
        }
    }

}  // namespace output

#endif  // OUTPUT_HPP

