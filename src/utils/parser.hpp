/*
    * parser.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * functions used to parse input file
    * changelog:
        - 09/29/2023 - header file created
        - 09/01/2023 - parser documentation improved
        - 10/20/2023 - formatted code
        - 10/31/2023 - changed to implement animal guessing game
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "global.hpp"
#include "output.hpp"

using namespace std;

namespace parser {
    namespace debug {
        void is_empty_file(bool is_empty);

        void ignoring_line(string line);

        void token_line(string token_line);

        void soup_of_letters_dim(int rows, int cols);

        void soup_of_letters(vector<vector<char>> soup_of_letters);

        void movies_to_search(vector<string> movie_titles_to_search);
    }  // namespace debug

    const char NOT_TOKENS[] = {'#', '\n'};

    inline bool is_comment_line(ifstream& input_file) {
        return input_file.peek() == '#';
    }

    inline bool is_empty_line(ifstream& input_file) {
        return input_file.peek() == '\n';
    }

    inline bool is_file_empty(ifstream& input_file) {
        return input_file.peek() == EOF;
    }

    /*
    This function defines what is a token line which is any line that the first
   character doesn't contain any NOT_TOKENS char.

    This definition is important since when the internal pointer of the ifstream
   file is at EOF it is considered a token line (see consume_file function
   documentation for more details of it's impotance).
*/
    inline bool is_token_line(ifstream& input_file) {
        char first_line_char = input_file.peek();
        bool is_token_line = true;           // assert the first char is not a NOT_TOKENS char
        for (char not_token : NOT_TOKENS) {  // check universally for all NOT_TOKENS chars
            is_token_line = is_token_line && (first_line_char != not_token);
        }
        return is_token_line;
    }

    /*
    This function is called to assert that the internal pointer of the ifstream
   file is not at the end of the file. Note that the end of the file is a token
   line (see is_token_line function).

    If it is the case that the pointer is at the end of the file and this
   functions was called, it means the program tried to read a non-empty token
   line (e.i the rows and columns dimensions line), but the file was empty. The
   program should recover at this point asking a new input file to the user.
   Since working this without having advance tools, such as the option<type>
   feature, its a nightmare in my opinion, I decided to just assume that the
   input file will always have the expected two blocks of tokens.
*/
    inline void assert_non_empty_file(ifstream& input_file) {
        if (is_file_empty(input_file)) {
            output::error_nonexpected("input file is empty");
        }
    }

    /*
    A helper function for get_next_token_line. All comment and empty lines that
   should be ignored by the parser are handled by this function.

    One result of the state of the ifstream file passed, the function always
   advances it's internal pointer to the next token line.
*/
    inline void advance_to_token(ifstream& input_file) {
        string line;
        while (!is_token_line(input_file)) {
            getline(input_file, line);
            parser::debug::ignoring_line(line);
        }
    }

    /*
    This function is used for to read lines fom the blocks of tokens.

*/
    inline string get_next_token_line(ifstream& input_file) {
        advance_to_token(input_file);
        string token_line;
        getline(input_file, token_line);
        parser::debug::token_line(token_line);
        return token_line;
    }

    /*
    This function is used to get the rows of the soup.
*/
    inline vector<string> get_token_block(ifstream& input_file, unsigned int block_size) {
        vector<string> token_block;
        while (token_block.size() < block_size) {
            string token_line = get_next_token_line(input_file);
            token_block.push_back(token_line);
        }
        return token_block;
    }

    /*
    Because the parser read the rows of the soup of letters as strings
   representing a line of letters (e.i "ABDFAFWEA"), this function is needed to
   convert the soup of letters from the vector of letter strings to a vector of
   vectors of chars.

    Example:
        1. vector<string> soup_str =   {"ABDFAFWEA",
                                        "ABDFAFWEA",
                                        "ABDFAFWEA"};
        2. vector<vector<char>> soup_char =
            {{'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'},
            {'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'},
            {'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'}};

    This conversion is needed since the movie searcher algorithm uses a vector
   of vectors of chars to represent the soup of letters instead of a vector of
   strings.

    If an empty vector of strings is passed, an empty vector of vectors of chars
   should be returned.
*/
    inline vector<vector<char>> soup_str_to_char(const vector<string>& soup_str) {
        vector<vector<char>> soup_char;
        for (const string& line : soup_str) {
            vector<char> line_char;
            for (char letter : line) {
                line_char.push_back(letter);
            }
            soup_char.push_back(line_char);
        }
        return soup_char;
    }

    /*
    It's expected to be the first parser function called to read tokens from the
   input file. The function assumes that the first token line is the dimensions
   of the soup of letters and then reads the subsequent lines to form the soup
   of letters.
*/
    inline vector<vector<char>> soup_letters(ifstream& input_file) {
        string soup_dim_line = get_next_token_line(input_file);
        int num_rows = stoi(soup_dim_line);
        int num_cols = stoi(soup_dim_line);
        vector<string> soup_str = get_token_block(input_file, num_rows);
        vector<vector<char>> soup = soup_str_to_char(soup_str);
        debug::soup_of_letters(soup);
        debug::soup_of_letters_dim(num_rows, num_cols);
        return soup;
    }

    /*
    This function is used to read the movie titles to search tokens. Notice that
   is practically the same to get_token_block() but it doesn't have a block size
   parameter which means that the file will be consumed after this function is
   called.
*/
    inline vector<string> consume_file(ifstream& input_file) {
        vector<string> token_block;
        while (!is_file_empty(input_file)) {
            string token_line = get_next_token_line(input_file);
            token_block.push_back(token_line);
        }
        parser::debug::is_empty_file(true);

        // The last token line is always an empty line. To see this read the
        // definition of a token line in is_token_line function. Consequently, when
        // an empty file is read, it returns an empty string which has to be
        // removed.
        if (token_block.size() > 0) {
            token_block.pop_back();
        }

        return token_block;
    }

    /*
    It is assumed that before this function is called, the soup block of tokens
   was already read from the input file.

    Basically a wrapper function of consume_file() to convey a clearer meaning
   of what consume_file() is used for.

    One concern to be aware of is that this function essentially consumes the
   rest of the input file.
*/
    inline vector<string> movies_to_search(ifstream& input_file) {
        vector<string> movie_titles_to_search = consume_file(input_file);
        return movie_titles_to_search;
    }

    // ----------------------------------------
    // =--------------- DEBUG  ---------------=
    namespace debug {
        inline void is_empty_file(bool is_empty) {
            if (global::debug_flags::EMPTY_FILE) {
                output::debug("is file empty: ", is_empty ? "true" : "false");
            }
        }

        inline void ignoring_line(string line) {
            if (global::debug_flags::IGNORING_COMMENT_LINE) {
                output::debug("ignoring line: ", line);
            }
        }

        inline void token_line(string token_line) {
            if (global::debug_flags::TOKEN_LINE) {
                output::debug("token line: ", token_line);
            }
        }

        inline void soup_of_letters_dim(int rows, int cols) {
            if (global::debug_flags::SOUP_OF_LETTERS_DIM) {
                output::debug("soup of letters dimensions: ",
                              to_string(rows) + "x" + to_string(cols));
            }
        }

        inline void soup_of_letters(vector<vector<char>> soup_of_letters) {
            if (global::debug_flags::SOUP_OF_LETTERS) {
                output::debug("soup of letters ");
                for (vector<char> line : soup_of_letters) {
                    for (char letter : line) {
                        cout << letter << " ";
                    }
                    cout << endl;
                }
            }
        }

        inline void movies_to_search(vector<string> movie_titles_to_search) {
            if (global::debug_flags::MOVIE_TITLES) {
                output::debug("vector of movie titles to search: ");
                for (string movie : movie_titles_to_search) {
                    output::debug(movie);
                }
            }
        }
    }  // namespace debug
       // =------------- END OF DEBUG -------------=
       // ------------------------------------------

}  // namespace parser

#endif  // PARSER_HPP
