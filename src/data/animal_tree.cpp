/*
 * Animal Tree Implementation
 * file: animal_tree.cpp
 * author: Diego R.R.
 * started: 10/29/2023
 * course: CS2337.501
 * 
 * This file contains implementations used for the AnimalTree structure, 
 * a structure designed to aid in the development of an animal guessing game.
 * 
 * The primary goal of this implementation is to enable the system to guess 
 * the animal a user is thinking of by traversing a binary tree of questions 
 * and answers. If the system fails to guess correctly, it collects more information 
 * from the user, expanding its knowledge for future sessions.
 *
 * Decision for creation:
 * This tree-based approach was chosen to facilitate dynamic learning. With this tree structure, 
 * the system can grow and evolve based on interactions with users. 
 *
 * changelog:
 *  10/29/2023 - initial implementation
 *  10/30/2023 - added play_game Functionalities
 *  10/31/2023 - added ostream functionality
 *
 * notes:
 *  1. TAKE INTO ACCOUNT THAT DEBUG FUNCTIONS are enabled through the global debug flags.
 *  2. Consider adding more error-handling procedures, especially when working with memory 
 *     allocation and tree modifications.
 */
#include <iostream>

#include "animal_node.hpp"
#include "animal_tree.hpp"
#include "global.hpp"
#include "input.hpp"
#include "output.hpp"

using namespace std;
using namespace animal_node;

namespace animal_tree {

    /**
     * @brief Default constructor. Initializes the tree with a default guess of "lizard".
     */
    AnimalTree::AnimalTree() {
        root = animal_node::alloc_animal("lizard");
    }

    bool is_question_type(const string& token) {
        return global::fncs::contains(token, "q");
    }

    bool is_animal_type(const string& token) {
        return global::fncs::contains(token, "g");
    }

    /**
    * Recursively constructs an AnimalNode from a vector of tokens.
    * This function utilizes a depth-first traversal mechanism to construct
    * the tree from the provided token list.
    *
    * @param tokens A vector of string tokens which represent the structure and content of the tree.
    * @param index A pointer to an integer representing the current position in the tokens list.
    * @return AnimalNode* A pointer to the constructed node (either a question node or an animal node).
    */
    AnimalNode* fill_node(const vector<string>& tokens, int* index) {
        if (*index > (tokens.size() + 2)) {
            output::error_nonexpected("index out of bounds");
        }

        string token_type = tokens[*index];
        debug::print_step(token_type, *index, tokens.size(), "type");
        (*index)++;

        string content = tokens[*index];
        debug::print_step(content, *index, tokens.size(), "content");
        (*index)++;

        // Check if current token is a question type.
        // If it is, then process its 'yes' and 'no' branches.
        if (is_question_type(token_type)) {
            AnimalNode* yes_branch = fill_node(tokens, index);
            AnimalNode* no_branch = fill_node(tokens, index);
            return alloc_question(content, yes_branch, no_branch);
        }
        // If current token is an animal type, process it.
        else if (is_animal_type(token_type)) {
            return alloc_animal(content);
        }
        // Error handling: Invalid token type.
        else {
            output::error("Invalid token type, very probably the input file is not in correct format" + token_type);
            return nullptr;
        }
    }

    AnimalTree::AnimalTree(const vector<string>& tokens) {
        int* index = new int(0);
        root = fill_node(tokens, index);
    }

    /**
     * @brief Starts the animal guessing game.
     *
     * Initiates the game, which will traverse the tree. Asking the user 
     * questions until it reaches a guess or needs to expand its knowledge, its 
     * handled by main.
     */
    void AnimalTree::play_game() {
        play_game(root);
    }

    /**
     * @brief Recursive function to traverse the tree and play the game.
     *
     * If the current node is a question, it asks the user the question and 
     * moves to the corresponding branch based on the answer. If it's an animal, 
     * the game makes a guess. If the guess is wrong, the game tries to expand its knowledge.
     *
     * @param node The current node in the traversal.
     */
    void AnimalTree::play_game(AnimalNode* node) {
        if (!node) {
            output::error("Traversing a null node");
            return;
        }

        if (node->is_question()) {
            string question = node->str;
            string ans = input::line(question + " (y/n): ");
            if (global::fncs::contains(ans, "y")) {
                play_game(node->yes_branch);
            } else {
                play_game(node->no_branch);
            }
        } else {
            // Guess the animal
            string guess = "Is it a(n) " + node->str + "? (y/n): ";
            string ans = input::line(guess);

            if (global::fncs::contains(ans, "y")) {
                output::inform("Yay! I guessed right!");
            } else {
                expand_animal_guess(node);
            }
        }
    }

    /**
     * @brief Expands the tree with a new animal and differentiating question.
     *
     * When the game fails to guess the correct animal, it asks the user for 
     * the correct animal and a question that differentiates it from the guessed one. 
     * The tree then expands its knowledge using this information.
     *
     * @param animal_node The incorrect guessed animal node to be expanded.
     */
    void AnimalTree::expand_animal_guess(AnimalNode*& animal_node) {
        string correct_animal = input::line("What animal were you thinking of?");
        string diff = input::line("What question identifies " + animal_node->str + " from " +
                                  correct_animal + "? (yes for " + correct_animal + ")");

        flip_to_question(animal_node, diff, correct_animal);

        output::inform("Thanks for teaching me!");
        output::separate();
    }

    /**
     * @brief Converts an animal node to a question node.
     *
     * This is used to expand the tree's knowledge. The given animal node is 
     * turned into a question node that differentiates between the originally 
     * guessed animal and the correct animal provided by the user.
     *
     * @param animal_node The animal node to be transformed.
     * @param question The differentiating question.
     * @param correct_animal The correct animal guessed by the user.
     */
    void AnimalTree::flip_to_question(AnimalNode*& animal_node, const string& question,
                                      const string& correct_animal) {
        AnimalNode* yes_node = alloc_animal(correct_animal);
        AnimalNode* no_node = alloc_animal(animal_node->str);
        animal_node->str = question;
        animal_node->yes_branch = yes_node;
        animal_node->no_branch = no_node;

        debug::flip_to_question(*animal_node);
    }

    // public print tree function
    void AnimalTree::print_tree(ostream& output_stream) {
        print_tree(output_stream, root, 0);
    }

    // recursive print tree function
    void AnimalTree::print_tree(ostream& output_stream, AnimalNode* root, int level) {
        if (!root) {
            return;
        }

        for (int i = 0; i < level; i++) {
            output_stream << " ";
        }

        if (root->is_question()) {
            output_stream << "Q " << root->str << endl;
            print_tree(output_stream, root->yes_branch, level + 1);
            print_tree(output_stream, root->no_branch, level + 1);
        } else {
            output_stream << "G " << root->str << endl;
        }
    }

    namespace debug {
        void print_tree(const AnimalTree& tree) {
            output::toDO("Print Tree Functionality To Be Implemented");
        }

        /**
         * @brief Debug function to inspect a given node.
         *
         * Prints node data with an additional "Inspecting" prefix.
         *
         * @param node The node to be inspected.
         * @param opt Additional optional information for debug output.
         */
        void inspecting_node(const AnimalNode& node, const string& opt) {
            if (global::debug_flags::INSPECTING_NODE) {
                animal_node::debug::print_node_data(node, opt + "Inspecting ");
            }
        }

        /**
         * @brief Debug function to inspect a given node.
         *
         * Prints node data with an additional "Inspecting" prefix.
         *
         * @param node The node to be inspected.
         * @param opt Additional optional information for debug output.
         */
        void flip_to_question(const AnimalNode& node) {
            if (global::debug_flags::FLIPPING) {
                animal_node::debug::print_node_data(node, "Flipping animal to ");
            }
        }

        void print_step(const string& content, int index, int size, const string& type) {
            if (global::debug_flags::PRINT_STEP) {
                cout << "DEBUG: " << "index: " << index << "/" << size << ", " << type << ": " << content << endl;           
            }
        }
    }  // namespace debug

}  // namespace animal_tree
