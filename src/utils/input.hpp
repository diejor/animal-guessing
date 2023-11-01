/*
 * Input Handling Module for User Interaction
 * file: input.hpp
 * author: Diego R.R.
 * date started: 10/16/2023
 * course: CS2337.501
 * 
 * This module provides various utility functions focused on retrieving 
 * user input in different forms. It aids in reading lines of input,
 * integers within certain ranges, file names with valid extensions, 
 * and ensures files exist before trying to open them.
 *
 * Special emphasis has been put on user experience by providing 
 * error messages when the input is not as expected and guiding 
 * the user to provide the correct input format.
 * 
 * The module also contains debugging routines to aid during the 
 * development phase.
 * 
 * changelog:
 *  10/16/2023 - initial completion
 *  10/22/2023 - fixed bug related to non-integer input handling
 *  10/29/2023 - refactored to support the animal guessing homework;
 *               removed integer_within_threasold function
 * 
 * notes:
 *  - Modular and extensible design: New input formats or constraints can 
 *    easily be added.
 *  - Input validation: Emphasis on guiding the user and ensuring valid input 
 *    is received.
 *  - Debugging support: Built-in debug utilities for development.
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
     * Debug routines 
     *
     * These functions are used for logging and debugging purposes. When the 
     * global debug flag for USER_INPUT is set, these routines will log 
     * information about user input.
     */
    namespace debug {

        // Logs the user input when the debug flag is enabled.
        inline void user_input(const string& input) {
            if (global::debug_flags::USER_INPUT) {
                output::debug("user input =" + input);
            }
        }

    }  // namespace debug

    /* 
     * Extensions
     *
     * Functions in this namespace are used to validate file extensions, 
     * ensuring that the user is working with the correct type of files.
     */
    namespace extensions {
        const string EXTENSIONS[] = {".txt"};

        // Checks if a given file has a specific extension.
        inline bool has(const string& file_name, const string& extension) {
            return file_name.find(extension) != string::npos;
        }
        
        // Checks if a given file has any of the valid extensions.
        inline bool has(const string& file_name) {
            bool has_extension = false;
            for (const string& extension : EXTENSIONS) {
                if (has(file_name, extension)) {
                    has_extension = true;
                    break;
                }
            }
            return has_extension;
        }

        // Checks if a given file has any valid extension except a specific one.
        inline bool has_except(const string& file_name, const string& extension) {
            bool has_extension = false;
            for (const string& ext : EXTENSIONS) {
                if (has(file_name, ext) && ext != extension) {
                    has_extension = true;
                    break;
                }
            }
            return has_extension;
        }
    }  // namespace extensions

    /* 
     * Function to get a line of input from the user.
     * The function will continue to ask for input until a non-empty string is provided.
     */
    inline string line(const string& msg) {
        string input;
        output::ask_for_input(msg);
        getline(cin, input);

        if (input.empty()) {
            output::error("input is empty");
            return line(msg);
        }

        string no_whitespace = global::fncs::trim_whitespace(input);
        debug::user_input(no_whitespace);
        return no_whitespace;
    }

     /*
     * Gets a validated filename from the user.
     * Ensures that the file provided by the user has a valid extension.
     */
    inline string get_file_name_validated() {
        string input_file_name = line(global::msgs::ENTER_FILE_NAME);

        while (!extensions::has(input_file_name)) {
            output::error("invalid file extension");
            input_file_name = line(global::msgs::ENTER_FILE_NAME_AGAIN);
        }
        return input_file_name;
    }

    /* 
     * Tries to open a file with the given filename.
     * If the file does not exist, it prompts the user for a filename again until 
     * a valid one is provided.
     */
    inline ifstream try_open_file(string input_file_name) {
        ifstream input_file;
        input_file.open(input_file_name);  // assert that the file exists
        while (!input_file.is_open()) {
            output::error("file does not exist");
            input_file_name = line(global::msgs::ENTER_FILE_NAME_AGAIN);
            input_file.open(input_file_name);
        }
        return input_file;
    }

    /* 
     * Main function to retrieve an input file.
     * Gets a filename from the user, ensures it's valid, then opens and returns the file.
     */
    inline ifstream get_input_file() {
        ifstream input_file;
        string input_file_name = get_file_name_validated();
        input_file = try_open_file(input_file_name);
        output::inform("file opened successfully");
        return input_file;
    }

    /* 
     * Retrieves an integer input from the user.
     * If the user does not provide an integer, they are prompted again until 
     * a valid integer is provided.
     */
    inline int integer(const string& msg) {
        int input;
        output::ask_for_input(msg);
        while (!(cin >> input)) {
            output::error("invalid input");
            output::ask_for_input(msg + " (must be an integer)");
            cin.clear();            // Clear the error state.
            cin.ignore(100, '\n');  // Discard non-integer input.
        }
        cin.ignore(1, '\n');  // Discard the newline character.
        debug::user_input(to_string(input));
        return input;
    }

    /* 
     * Retrieves an integer within a specified range.
     * Keeps prompting the user until they provide an integer within the given range.
     */
    inline int integer_within_range(const string& msg, int min, int max) {
        int input = integer(msg);
        while (input < min || input > max) {
            output::error("input must be between " + to_string(min) + " and " + to_string(max));
            input = integer(msg);
        }
        return input;
    }

    /*
     * Presents the user with a list of options and gets their selection.
     * Returns the index of the selected option.
     */
    inline int select(const string& msg, const vector<string>& options) {
        output::select(msg, options);
        int input = integer_within_range("Enter your selection: ", 1, options.size());
        return input;
    }
}  // namespace input

#endif  // INPUT_HPP
