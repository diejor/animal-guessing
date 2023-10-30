/*
 * Animal Tree Structure
 * file: animal_tree.hpp
 * author: Diego R.R.
 * started: 10/29/2023
 * course: CS2337.501
 *
 * structure used to represent the tree in the animal guessing game
 *
 * changelog:
 *  10/29/2023 - started animal tree design
 *
 * notes:
 */

#ifndef ANIMAL_TREE_HPP
#define ANIMAL_TREE_HPP

#include "animal_node.hpp"

namespace animal_tree {

    struct AnimalTree {
        animal_node::AnimalNode* root;

        AnimalTree();

        // traverse the tree and play the game
        void play_game();

    private:
        void play_game(animal_node::AnimalNode* root);

        void insert_question(
                animal_node::AnimalNode*& null_node,
                const std::string& question, 
                const std::string& yes_animal, 
                const std::string& no_animal
        );
        void insert_animal(
                animal_node::AnimalNode*& null_node,
                const std::string& animal
        );
    }; 

    // Debug routines
    namespace debug {
        void print_tree(const AnimalTree& tree);
    } 

}  // namespace animal_tree

#endif  // ANIMAL_TREE_HPP

