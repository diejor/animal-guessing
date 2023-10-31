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

const string PROGRAM_TITLE =
"    _          _                 _    ____                     _             \n"
"   / \\   _ __ (_)_ __ ___   __ _| |  / ___|_   _  ___  ___ ___(_)_ __   __ _ \n"
"  / _ \\ | '_ \\| | '_ ` _ \\ / _` | | | |  _| | | |/ _ \\/ __/ __| | '_ \\ / _` |\n"
" / ___ \\| | | | | | | | | | (_| | | | |_| | |_| |  __/\\__ \\__ \\ | | | | (_| |\n"
"/_/___\\_\\_| |_|_|_| |_| |_|\\__,_|_|  \\____|\\__,_|\\___||___/___/_|_| |_|\\__, |\n"
" / ___| __ _ _ __ ___   ___                                             \\___/ \n"
"| |  _ / _` | '_ ` _ \\ / _ \\                                                 \n"
"| |_| | (_| | | | | | |  __/                                                 \n"
" \\____|\\__,_|_| |_| |_|\\___|                                                 ";

namespace output {
    inline void ask_for_input(const string& msg) {
        cout << msg;
    }

    inline void error(const string& msg) {
        cout << "ERROR NOT EXPECTED: " << msg << endl;
    }

    inline void debug(const string& msg) {
        cout << "DEBUG: " << msg << endl;
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
        cout << PROGRAM_TITLE << endl;
    }

    inline void init_game() {
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "             Welcome to the Animal Guess Game!         \n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

        cout << "\nIn this game, I will become an investigator to guess the animal you are" <<
           "thinking of by asking -.- you questions.\n";
        cout << "All you need to do is answer my questions with a 'y' for yes or 'n' for no.\n";
        cout << "Certainly if I can't guess the correct animal, then I will learn from my mistakes!\n";
        cout << "By the end, I'll become smarter and better at this game and maybe conquest the world.\n";
        cout << "\nAre you ready to challenge me? Let the game begin!\n";
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
