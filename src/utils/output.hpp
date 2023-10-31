#ifndef OUTPUT_HPP
#define OUTPUT_HPP
/*
 * title: Output Handler
 * file: output.hpp
 * author: Diego R.R.
 * started: 10/16/2023
 * course: CS2337.501
 *
 * functions to output information to the user
 *
 * changelog:
 * 10/29/2023 - changed to implement animal guessing homework, vector table removed
 */


#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>


#include "global.hpp"

using namespace std;


namespace output {
    inline void ask_for_input(const string& msg) {
        cout << msg;
    }

    inline void error(const string& msg) {
        cout << "ERROR: " << msg << endl;
    }

    inline void error_nonexpected(const string& msg) {
        cout << "ERROR NOT EXPECTED: " << msg << endl;
    }

    inline void debug(const string& msg) {
        cout << "DEBUG: " << msg << endl;
    }

    inline void debug(const string& msg, const string& opt) {
        cout << "DEBUG: " << msg << opt << endl;
    }

    inline void toDO(const string& msg) {
        cout << "!!!!!!!!TO DO!!!!!!: " << msg << endl;
    }

    inline void repeat(const string& str, int times) {
        for (int i = 0; i < times; i++) {
            cout << str;
        }
    }

    inline void separate() {
        cout << endl;
    }

    inline void inform(const string& msg) {
        cout << "  ~  " << msg << endl;
    }

    inline void welcome() {
        cout << global::msgs::PROGRAM_TITLE << endl;
    }

    inline void init_game() {
        cout << global::msgs::INIT_GAME << endl;
        separate();
    }

    inline void goodbye() {
        cout << global::msgs::GOODBYE << endl;
    }

    /*
    *  Displays a line, used to display the header and footer of the vector table.
    */
    inline void line(int length) {
        cout << "+";
        repeat("-", length);
        cout << "+" << endl;
    }

    /*
    *  Displays a message in a box with the message centered.
    *  Used to display the header of the vector table.
    */
    inline void boxed_centered(const string& msg, int box_len) {
        int msg_len = msg.length();
        if (msg_len > box_len)
            box_len = msg_len;
        int left_spaces = (box_len - msg_len) / 2;
        int right_spaces = box_len - msg_len - left_spaces;

        line(box_len + 2);
        cout << "| ";
        repeat(" ", left_spaces);
        cout << msg;
        repeat(" ", right_spaces);
        cout << " |" << endl;
        line(box_len + 2);
    }

    
    inline void select(const string& msg, const vector<string>& options) {
        cout << msg << " (select a number)" << endl;
        for (int i = 0; i < options.size(); i++) {
            cout << "\t" << i + 1 << ". " << options[i] << endl;
        }
    }
} // namespace output

#endif // OUTPUT_HPP
