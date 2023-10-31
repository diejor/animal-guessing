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
 * Project Structure:
 * 1. input.hpp - Handles input operations.
 * 2. output.hpp - Manages the output displays and debug messages.
 * 3. animal tree - Provides the main structure and logic for the guessing game.
 *    3.1 animal_tree.cpp - implementations for the AnimalTree structure.
 * 4. animal_node - Defines the building blocks of the tree.
 *
 * Changelog:
 *  - 10/27/2023 - initial design.
 *  - 10/28/2023 - included input and output utils,
 *  - 10/29/2023 - main development of app.
 *  - see other files for changelog, for more detailed information.
 *  - 10/30/2023
 *    - added decisions.
 *
 * Notes:
 * - The game utilizes a decision tree mechanism for its logic.
 * - With each incorrect guess, the game learns by adding new questions and animals to its knowledge base.
 * - The "separate" function from the output namespace is used to create a separation in the console between game rounds.
 *
 */

#include <iostream>

using namespace std;

#include "input.hpp"
#include "output.hpp"
#include "animal_tree.hpp"

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

animal_tree::AnimalTree init_tree() {
    vector<string> selection = {
        "Create from database", 
        "Create from scratch", 
        "Create randomly"
    };
    int choice = input::select(
            "Gimme a choice to initialize the decision tree", selection);
    output::separate();
    animal_tree::AnimalTree tree;

    switch (choice) {
        case 1:
            tree = animal_tree::AnimalTree();
            break;
        case 2:
            tree = animal_tree::AnimalTree();
            break;
        case 3:
            tree = animal_tree::AnimalTree();
            break;
        default:
            output::error("invalid choice");
            break;
    }
    output::separate();

    return tree;
}

void decide_action(animal_tree::AnimalTree& tree) {
    vector<string> selection = {
        "Play game", 
        "Print tree", 
        "Save tree", 
        "dile adios al arbol (new tree)",
        "Exit of Game"
    };
    int choice = input::select("Now what?", selection);
    output::separate();

    switch (choice) {
        case 1:
            output::init_game();
            tree.play_game();
            break;
        case 2:
            tree.print_tree(cout);
            break;
        case 3:
            output::toDO("save tree");
            break;
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

int main() {
    output::welcome();
    output::separate();

    animal_tree::AnimalTree tree = init_tree();
    
    do {
        decide_action(tree);
    } while (play_again("Leaving the game :(? (y/n)"));

    exit_game();

    return 0;
}
