CXX ?= g++
CXXFLAGS = --std=c++11 -Wall -Werror -pedantic -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

# compiling the main executable
sudoku.exe: sudoku.cpp grid.cpp solve.cpp iterator.cpp
	$(CXX) $(CXXFLAGS) sudoku.cpp grid.cpp solve.cpp iterator.cpp -o sudoku.exe

# disable built-in rules
.SUFFIXES:

# these targets do not create any files
.PHONY: clean
clean :
	rm -vrf *.o *.exe *.gch *.dSYM *.stackdump *.out.txt
