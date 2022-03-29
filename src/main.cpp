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
using std::cerr;
using std::exception;

// Wrapping program execution in try catch to ensure clean-ups are performed.
int main()
{
    try {
        // Execute and return exit code.
        return program_main();
        // return program_main_ncurses();
    } catch (const exception& e) {
        cerr << "\n\n### EXCEPTION CAUGHT: " << e.what() << " ###\n\n\a";
    } catch (...) {
        cerr << "\n\n### UNKNOWN EXCEPTION OCCURRED. ###\n\n\a";
    }
}
