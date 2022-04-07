/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Aotian Chen   , Hieu Duong
// St.# : 301360315     , 301380066
// Email: aca189@sfu.ca , hieu_duong@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#include "program_main.h"
#include <iostream>
#include <stdexcept>

void reset_cin() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int main() {
    // Ensure cleanup in case of exception.
    try {
        std::cout << "\nChoose a terminal mode to run in.\n"
                     "\n"
                     "(1) Regular mode. [Stable]\n"
                     "(2) With ncurses. [Experimental]\n"
                     "\n"
                     "Enter your option: ";
        int mode = 0;
        std::cin >> mode;
        // Handle invalid input.
        while (!std::cin || (std::cin.peek() != '\n') || (mode < 1) || (mode > 2)) {
            reset_cin();
            std::cout << "Invalid mode. Please try again: ";
            std::cin >> mode;
        }
        reset_cin();
        // Execute accordingly and return exit code.
        return (mode == 2) ? program_main_ncurses() : program_main();
    } catch (const std::exception& e) {
        std::cerr << "\n\n### EXCEPTION CAUGHT: " << e.what() << " ###\n\n\a";
    } catch (...) {
        std::cerr << "\n\n### UNKNOWN EXCEPTION OCCURRED. ###\n\n\a";
    }
}