#include <iostream>

using namespace std;

#include "input.hpp"
#include "output.hpp"

int main() {
    int number = input::integer("Enter a number: ");
    string is_even = number % 2 == 0 ? "even" : "odd"; 
    output::boxed_centered(is_even, 20);
    return 0;
}
