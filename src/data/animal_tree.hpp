/*
 * Animal Tree Structure
 * file: animal_tree.hpp
 * author: Diego R.R.
 * started: 10/29/2023
 * course: CS2337.501
 *
 * purpose: 
 * structure used to represent the tree in the animal guessing game
 *
 * changelog:
 *  10/29/2023 - started animal tree design
 
 */

#ifndef ANIMAL_TREE_HPP
#define ANIMAL_TREE_HPP

#include <fstream>
#include "animal_node.hpp"

using namespace std;


namespace animal_tree {

    struct AnimalTree {
        animal_node::AnimalNode* root;

        // Default constructor
        AnimalTree();

        // Constructor from database
        AnimalTree(const vector<string>& tokens);

        // traverse the tree and play the game
        void play_game();

        // print tree to ofstream 
        void print_tree(ostream& output_file);
    private:
        // Recursive function to traverse the tree and play the game
        void play_game(animal_node::AnimalNode* root);

        // see cpp
        void expand_animal_guess(animal_node::AnimalNode*& current_node);

        // see cpp
        void flip_to_question(
                animal_node::AnimalNode*& animal_node,
                const string& question, 
                const string& correct_animal
        );

        // recursive function to ofstream handling
        void print_tree(ostream& output_stream, animal_node::AnimalNode* root, int level);
    }; 

    // Debug routines
    namespace debug {
        void print_tree(const AnimalTree& tree);
        void inspecting_node(const animal_node::AnimalNode& node, const string& opt = "");
        void flip_to_question(const animal_node::AnimalNode& node);
        void print_step(const string& content, int index, int size, const string& str);
    } 

}  // namespace animal_tree

#endif  // ANIMAL_TREE_HPP

