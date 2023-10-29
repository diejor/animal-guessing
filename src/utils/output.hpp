/*
 * title: Output Handler
 * file: output.hpp
 * author: Diego R.R.
 * started: 10/16/2023
 * course: CS2337.501
 *
 * functions to output information to the user
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
    const int COLUMNS_TABLE = 5;
    const int CELL_WIDTH = 5;

    void ask_for_input(const string& msg) { cout << msg; }

    void error(const string& msg) {
        cout << "ERROR: " << msg << endl;
    }

    void debug(const string& msg) {
        cout << "DEBUG: " << msg << endl;
    }

    void repeat(const string& str, int times) {
        for (int i = 0; i < times; i++) {
            cout << str;
        }
    }

    void separate() {
        cout << endl;
    }

    /*
    *  Displays a line, used to display the header and footer of the vector table.
    */
    void line(int length) {
        cout << "+";
        repeat("-", length);
        cout << "+" << endl;
    }

    /*
    *  Displays a message in a box with the message centered.
    *  Used to display the header of the vector table.
    */
    void boxed_centered(const string& msg, int box_len) {
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

    /*
    *   Used in output::show_vec() to count the number of occurrences of a number in a vector.
    */
    int occurrences(const vector<int> vec, int num) {
        int count = 0;
        for (int i : vec) {
            if (i == num) {
                count++;
            }
        }
        return count;
    }

    void show_vector(const vector<int>& vec) {
        int width = CELL_WIDTH * COLUMNS_TABLE;
        boxed_centered("Numbers", width + 2);
        for (int vec_idx = 0; vec_idx < vec.size(); vec_idx++) {
            int num = vec[vec_idx];
            int cols_idx = vec_idx % COLUMNS_TABLE;
            if (cols_idx == 0) { // if first column
                cout << "|";
            }
            int occur = occurrences(vec, num);
            string num_str = to_string(num);
            cout << setw(CELL_WIDTH) << num_str << "|";
            if (cols_idx == COLUMNS_TABLE - 1) { // if last column
                cout << endl;
                line(width + 4);
            }
        }

        if (vec.size() % COLUMNS_TABLE != 0) { // if last row is not full
            cout << endl;
            line(width + 4);
        }
    }


} // namespace output

#endif // OUTPUT_HPP
