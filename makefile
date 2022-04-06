###################################################################################################
#
# Makefile for assignment 5 of CMPT 135 Spring 2022, SFU Surrey.
#
# Modified from the original makefile by Toby Donalson.
#
# Cite: https://stackoverflow.com/a/63627557
#
# Commands for this makefile that can be typed at the command line:
#
#   make
#      Build the executable program `main` in ./src/ folder and clean up compiler's output files.
#
#   make -j
#      Build `main` possibly a little more quickly. The "-j" option tells
#      make to try to use multiple CPUs when compiling two, or more, files.
#
#   make all
#      Build the executable program `main` and unit tests files.
#      The details are defined by lower-level Makefile in ./src/ .
#
#   make clean
#      Delete everything the compiler just created.
#      The details are defined by lower-level Makefile in ./src/ .
#
#   make run
#      Run the program `main` in ./src/ .
#
#   make check
#      Build executable tests and run them all.
#      The details are defined by lower-level Makefile in ./src/ .
#
###################################################################################################

main:
# Call make main and make clean-build in ./src/Makefile
	$(MAKE) -C ./src/ $@
	$(MAKE) -C ./src/ clean-build

all:
# Call make all in ./src/Makefile
	$(MAKE) -C ./src/ $@

clean:
# Call make clean in ./src/Makefile
	$(MAKE) -C ./src/ $@

run:
# Call make run in ./src/Makefile
	$(MAKE) -C ./src/ $@

check:
# Call make tests and make check in ./src/Makefile
	$(MAKE) -C ./src/ tests $@

install-ncurses:
# Install ncurses on the system.
	sudo apt-get install libncurses5-dev libncursesw5-dev -y
	apt list --installed "*ncurses*"

doc:
# Run doxygen with the specified Doxyfile.
	doxygen ./docs/Doxyfile

dist:
# Zip all files and folders in current directory to a5.zip,
# except one folder and some files specified below.
# If zip is not installed, run:  sudo apt-get install zip -y
	zip -r a5.zip . -x ./a5.zip ./.gitignore "./tools/*"

distclean:
# Remove created zip file.
	rm -f a5.zip
