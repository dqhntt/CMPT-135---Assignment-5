####################################################################
#
# Makefile for CMPT 135 Spring 2021, SFU Surrey.
#
# References:
#     - Modified from the original makefile by Toby Donalson.
#     - https://makefiletutorial.com/#pattern-rules
#     - https://nullprogram.com/blog/2017/08/20/
#     - http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/#output
#     - https://www.gnu.org/software/make/manual/html_node/Makefiles.html
#     - https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html
#     - https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html
#     - https://www.gnu.org/software/make/manual/html_node/Pattern-Match.html
#     - http://www.gnu.org/software/make/manual/html_node/Prerequisite-Types.html
#
###################################################################################################

# For automatically building main program and executable tests.

# Changing implicit variables for make's built-in rules:

# Set the C++ compiler options:
#   -std=c++17 compiles using the C++17 standard (or at least as 
#    much as is implemented by the compiler, e.g. for g++ see
#    http://gcc.gnu.org/projects/cxx0x.html)
#   -Wall turns on all warnings
#   -Wextra turns on even more warnings
#   -Werror causes warnings to be errors 
#   -Wfatal-errors stops the compiler after the first error
#   -Wno-sign-compare turns off warnings for comparing signed and 
#    unsigned numbers
#   -Wnon-virtual-dtor warns about non-virtual destructors
#   -g puts debugging info into the executables (makes them larger)
CPPFLAGS := -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g
CPPFLAGS += -MMD -MP  # Tell compiler to generate makefiles for us, with .d extension.
LDLIBS   := -lncurses # Tell make to link ncurses libraries whenever linker is used.
CC       := $(CXX)    # Tell make to use g++ or equivalent when auto linking .o files.

# Explicit variables for use with make:

SRCS := $(wildcard *.cpp)  # Find all source files with .cpp extension.
DEPS := $(SOURCES:.cpp=.d) # Substitute all .cpp extension with .d from those above.

TEST_SRCS := $(wildcard *.test.cpp)
TESTS     := $(TEST_SRCS:.cpp=) # Executable tests have extension .test.

MAINS := main.cpp $(wildcard *.test.cpp)       # List all source files with `int main()` defined.
NO_MAIN_SRCS := $(filter-out $(MAINS),$(SRCS)) # Filter out all the above from the source files.

MAIN_SRCS := main.cpp $(NO_MAIN_SRCS) # List all source files that can be used to create `main`.

.DELETE_ON_ERROR: # Delete any target files that can't be made without errors.

all: main tests

# Change extension from .cpp to .o and tell make to automatically create these object files.
# When done, link them using the implicit variables above to output executable `main`.
main: $(MAIN_SRCS:.cpp=.o)

# Calling `make tests` create executable tests as defined in explicit variable `TESTS`.
tests: $(TESTS)

# Create executable tests from its .o file and all other .o files without `int main()` defined.
# Thus, all files *.test.cpp must have `int main()` defined.
$(TESTS): %.test : %.test.o $(NO_MAIN_SRCS:.cpp=.o)

check:
	for TEST in $(TESTS); do ./$$TEST; done;

check-main:
	valgrind ./main

run:
	./main

clean: clean-main clean-build clean-tests

clean-main:
	rm -f main

clean-build:
	rm -f *.d *.o
	
clean-tests:
	rm -f $(TESTS)

-include $(DEPS)
