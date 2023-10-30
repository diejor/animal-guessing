/*
 * Animal Node Implementation
 * file: animal_node.cpp
 * author: Diego R.R.
 * started: 10/29/2023
 * course: CS2337.501
 *
 * implementations used for the AnimalNode structure
 *
 * changelog:
 *  10/29/2023 - initial implementation
 *
 * notes:
 */

#include "animal_node.hpp"
#include "output.hpp"
#include <iostream>

using namespace std;

namespace animal_node {

    // Dynamically allocate a new question node
    AnimalNode* alloc_question(const string& question, AnimalNode* yes, AnimalNode* no) {
        AnimalNode* node = new AnimalNode;
        node->str = question;
        node->yes_branch = yes;
        node->no_branch = no;

        debug::print_node_data(*node);

        return node;
    }

    // Dynamically allocate a new animal node
    AnimalNode* alloc_animal(const string& animal) {
        AnimalNode* node = new AnimalNode;
        node->str = animal;
        node->yes_branch = nullptr;
        node->no_branch = nullptr;

        debug::print_node_data(*node);

        return node;
    }

    // Implement the debug function
    void debug::print_node_data(const AnimalNode& node) {
        if (global::debug_flags::ANIMAL_NODE) {
            if (node.is_question()) {
                output::debug("Question: " + node.str);
                if (node.yes_branch) {
                    output::debug("Yes Branch: " + node.yes_branch->str);
                } else {
                    output::error("Yes Branch is null");
                }
                if (node.no_branch) {
                    output::debug("No Branch: " + node.no_branch->str);
                } else {
                    output::error("No Branch is null");
                }
            }

            if (node.is_animal()) {
                output::debug("Animal: " + node.str);
            } else {
                output::error("Node type is not a question or animal");
            }
        }
    }

}  // namespace animal_node

