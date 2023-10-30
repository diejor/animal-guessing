/*
 * Animal Node Implementation
 * file: animal_node.cpp
 * author: Diego R.R.
 * started: 10/29/2023
 * course: CS2337.501
 *
 * Purpose:
 * Provides implementations for the AnimalNode structure which is primarily 
 * used for constructing a decision tree. This decision tree aids in distinguishing 
 * between different animals based on a series of questions.
 *
 * Key Functions:
 * 1. alloc_question: Allocates memory and sets up a new question node.
 * 2. alloc_animal: Allocates memory and sets up a new animal node.
 * 3. print_node_data: A debug function to print out node information.
 *
 * changelog:
 *  10/29/2023 - initial implementation, added debug function, added alloc functions
 *
 * notes:
 * - Ensure proper memory management to avoid memory leaks.
 */

#include "animal_node.hpp"
#include "output.hpp"
#include <iostream>

using namespace std;

namespace animal_node {

    /**
     * @brief Dynamically allocates and initializes a new question node.
     * 
     * This function dynamically allocates memory for a question node, 
     * initializes it with the provided question, yes branch, and no branch,
     * and then returns a pointer to the new node.
     *
     * @param question The question string.
     * @param yes Pointer to the yes branch.
     * @param no Pointer to the no branch.
     * @return Pointer to the dynamically allocated question node.
     */
    AnimalNode* alloc_question(const string& question, AnimalNode* yes, AnimalNode* no) {
        AnimalNode* node = new AnimalNode;
        node->str = question;
        node->yes_branch = yes;
        node->no_branch = no;

        debug::print_node_data(*node);

        return node;
    }

    /**
     * @brief Dynamically allocates and initializes a new animal node.
     * 
     * This function dynamically allocates memory for an animal node,
     * initializes it with the provided animal string, and then returns 
     * a pointer to the new node.
     *
     * @param animal The animal string.
     * @return Pointer to the dynamically allocated animal node.
     */
    AnimalNode* alloc_animal(const string& animal) {
        AnimalNode* node = new AnimalNode;
        node->str = animal;
        node->yes_branch = nullptr;
        node->no_branch = nullptr;

        debug::print_node_data(*node);

        return node;
    }

    /**
     * @brief Debug function to print node data.
     * 
     * Depending on the type of node (question or animal), this function
     * prints relevant node data. If it's a question node, it also ensures
     * that the branches are not null before printing.
     *
     * @param node The node whose data needs to be printed.
     * @param opt Optional string to provide context to the debug output.
     */
    void debug::print_node_data(const AnimalNode& node, const string& opt) {
        if (global::debug_flags::NODE_CREATED) {
            string type = node.is_question() ? "question" : "animal";
            if (node.is_question()) {
                AnimalNode* yes_node = node.yes_branch;
                AnimalNode* no_node = node.no_branch;

                if (!yes_node || !no_node) {
                    output::error("Question node has null branches");
                    return;
                }

                string yes_animal = yes_node->str;
                string no_animal = no_node->str;

                output::debug(opt + "question: (" + node.str + ", " + yes_animal + ", " + no_animal + ")");
            } else {
                output::debug(opt + "animal: " + node.str);
            }
        }
    }

}  // namespace animal_node

