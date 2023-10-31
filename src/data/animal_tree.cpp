/*
 * Animal Tree Implementation
 * file: animal_tree.cpp
 * author: Diego R.R.
 * started: 10/29/2023
 * course: CS2337.501
 *
 * implementations used for the AnimalTree structure
 *
 * changelog:
 *  10/29/2023 - initial implementation
 *
 * notes:
 */

#include "animal_tree.hpp"
#include <iostream>
#include "animal_node.hpp"
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
            string ans = input::line(question);
            if (global::fncs::contains(ans, "y")) {
                play_game(node->yes_branch);
            } else {
                play_game(node->no_branch);
            }
        } else {
            // Guess the animal
            string guess = "Is it a(n) " + node->str + "? (y/n)";
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
    }  // namespace debug

}  // namespace animal_tree
