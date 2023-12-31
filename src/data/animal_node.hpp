/*
 * Animal Node Structure
 * file: animal_node.hpp
 * author: Diego R.R.
 * started: 10/29/2023
 * course: CS2337.501
 *
 * purpose:
 * structure used to represent nodes in the animal guessing game
 *
 * changelog:
 *  10/29/2023 - started animal node design
 */

#ifndef ANIMAL_NODE_HPP
#define ANIMAL_NODE_HPP

#include <string>

#include "global.hpp"

using namespace std;


namespace animal_node {
    /*
     * Animal Node Structure, if has no branches, it is an animal, otherwise it is a question
     */
    struct AnimalNode {
        string str;  // Question or animal
        AnimalNode* yes_branch;     // Pointer to 'Yes' branch
        AnimalNode* no_branch;      // Pointer to 'No' branch
        
        bool is_question() const {
            return yes_branch && no_branch;
        }
        bool is_animal() const {
            return !yes_branch && !no_branch;
        }
    };

    /*
     *  creates a new question node 
     */
    AnimalNode* alloc_question(const string& question, AnimalNode* yes, AnimalNode* no);

    /*
     *  creates a new animal node
     */
    AnimalNode* alloc_animal(const string& animal);

    /*
     *  Debug routines
     */
    namespace debug {
        void print_node_data(const AnimalNode& node, const string& opt = "");
    }  // namespace debug

}  // namespace animal_node

#endif  // ANIMAL_NODE_HPP

