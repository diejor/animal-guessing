/*
 * Animal Guessing Machine
 * file: main.cpp
 * author: Diego R.R. 
 * date: 10/30/2023
 * course: CS2337.501
 *
 * Purpose:
 * The main entry point for an animal guessing game. This program aims to train 
 * and play with a machine that guesses animals based on a series of yes/no questions.
 * The more it's played with, the better it becomes at guessing the correct animals.
 *
 * Functionality:
 * - The game utilizes a decision tree mechanism for its logic.
 * - With each incorrect guess, the game learns by adding new questions and animals to its knowledge base.
 * - The "separate" function from the output namespace is used to create a separation in the console between game rounds.
 *
 * Project Structure:
 * 1. global.hpp - Contains global constants and debug flags.
 * 2. input.hpp - Handles input operations.
 * 3. output.hpp - Manages the output displays and debug messages.
 * 4, parser.hpp - Handles the parsing of the input file used to read databases.
 * 4. animal tree - Provides the main structure and logic for the guessing game.
 *    3.1 animal_tree.cpp - implementations for the AnimalTree structure.
 * 5. animal_node - Defines the building blocks of the tree.
 *
 * Changelog:
 *  - 10/27/2023 - initial design.
 *  - 10/28/2023 - included input and output utils,
 *  - 10/29/2023 - main development of app.
 *  - see other files for changelog, for more detailed information.
 *  - 10/30/2023
 *    - added decisions.
 *    - added printing.
 *    - added goodbye message.
 *    - added more documentation.
 *  - 10/31/2023
 *    - added more documentation.
 *    - added save/load functionality.
 *
 * Notes:
 * - !!!!!! IMPORTANT !!!!!
 *   - To enable debugging tools, simply set the appropriate flag inside the 
 *   `debug_flags` namespace to `true` in the global.hpp file.
 * - Take into account that most of the logic of the program is contained in the 
 *   animal_tree module. The main function is used to initialize the game.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "animal_tree.hpp"
#include "input.hpp"
#include "output.hpp"
#include "parser.hpp"

/**
 * @brief Queries the user if they want to continue playing.
 * 
 * Prompts the user with a given message and checks if their response contains a 'y' indicating a positive response.
 *
 * @param msg The prompt message to be displayed.
 * @return True if user wants to play again, false otherwise.
 */
bool play_again(const string& msg) {
    string ans = input::line(msg);
    output::separate();
    return !global::fncs::contains(ans, "y");
}

void exit_game() {
    output::goodbye();
    exit(0);
}

/**
 * @brief Initialize the animal guessing tree either from a database or from scratch.
 * @return animal_tree::AnimalTree The initialized animal tree.
 */
animal_tree::AnimalTree init_tree() {
    vector<string> selection = {"Create from database", "Create from scratch"};
    int choice = input::select(global::msgs::DECISION, selection);
    output::separate();
    animal_tree::AnimalTree tree;

    switch (choice) {
        case 1: {
            ifstream input_file = input::get_input_file();
            vector<string> tokens = parser::consume_file(input_file);
            tree = animal_tree::AnimalTree(tokens);
            output::inform("tree created from database");
            break;
        }
        case 2:
            tree = animal_tree::AnimalTree();
            break;
        default:
            output::error("invalid choice");
            break;
    }
    output::separate();

    return tree;
}

/**
 * @brief Decide which action to perform based on user input: play the game, print/save the tree, restart, or exit.
 * @param tree Reference to the animal guessing tree.
 */
void decide_action(animal_tree::AnimalTree& tree) {
    vector<string> selection = {"Play game", "Print tree", "Save tree",
                                "dile adios al arbol (new tree)", "Exit of Game"};
    int choice = input::select("Now what?", selection);
    output::separate();

    switch (choice) {
        case 1:
            output::init_game();
            tree.play_game();
            break;
        case 2:
            output::inform("printing tree");
            tree.print_tree(cout);
            break;
        case 3: {
            output::inform("saving tree");
            string output_file_path = input::line(global::msgs::OUTPUT_FILE_PATH);
            ofstream output_file(output_file_path);
            tree.print_tree(output_file);
        } break;
        case 4:
            tree = init_tree();
            break;
        case 5:
            exit_game();
            break;
        default:
            output::error("invalid choice");
            break;
    }
    output::separate();
}

/**
 * @brief Main entry point of the program.
 * Initializes the game and continuously offers the user choices of actions.
 * @return int 0 for successful execution.
 */
int main() {
    output::welcome();
    output::separate();

    animal_tree::AnimalTree tree = init_tree();

    while (true)
        decide_action(tree);

    output::error_nonexpected("THIS SHOULD NOT BE REACHABLE: game exists with decide_action()");

    return 0;
}
