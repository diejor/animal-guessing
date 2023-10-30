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
    return global::fncs::contains(ans, "y");
}

int main() {
    // Initialize the game tree, using the default constructor of animal_tree::AnimalTree
    // This will initialize the tree with a default guess of "lizard"
    // See animal_tree.cpp for more documentation
    animal_tree::AnimalTree tree = animal_tree::AnimalTree();

    // Game loop
    do {
        tree.play_game(); // see animal_tree.cpp for more documentation
        output::separate();
    } while (play_again("can I guess again? (y/n)"));
    return 0;
}
