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
#include "animal_node.hpp"
#include "global.hpp"
#include "input.hpp"
#include "output.hpp"
#include <iostream>

using namespace std;
using namespace animal_node;

namespace animal_tree {

    // Default constructor, guesses lizard
    AnimalTree::AnimalTree() {
        AnimalNode* root = animal_node::alloc_animal("lizard");
    }

    void AnimalTree::play_game() {
        play_game(root);
    }

    // Recursive function to play the game
    void AnimalTree::play_game(AnimalNode* root) {
        output::toDO("Play Game Functionality To Be Implemented");
    }

    void AnimalTree::insert_question(
            AnimalNode*& null_node,
            const string& question, 
            const string& yes_animal, 
            const string& no_animal
    ) {
        AnimalNode* yes_node = alloc_animal(yes_animal);
        AnimalNode* no_node = alloc_animal(no_animal);
        AnimalNode* question_node = alloc_question(question, yes_node, no_node);
        null_node = question_node;
    }

    void AnimalTree::insert_animal(AnimalNode*& null_node, const string& animal) {
        AnimalNode* animal_node = alloc_animal(animal);
        null_node = animal_node;
    }

    void debug::print_tree(const AnimalTree& tree) {
        // Placeholder, you can expand on this to actually print the entire tree
        output::toDO("Print Tree Functionality To Be Implemented");
    }

}  // namespace animal_tree

