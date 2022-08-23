# sudoku-solver
Use this program to solve sudoku puzzles

This program uses my own implementation of the backtracking
algorithm described in this wikipedia article:
https://en.wikipedia.org/wiki/Sudoku_solving_algorithms

Input a sudoku puzzle into the tes1.txt file. Represent exmpty squares with a zero.
Be sure to pass in the file name as a command line argument. For example:
./executable test.txt

There is currently a sample grid in the input file. This is not a valid puzzle but it
demonstrates the proper formatting of the file.

Remember to include the spaces

The data structure used to represent the sudoku grid consists of nine horizontal linked lists
that are also connected vertically to form the grid. A custom iterator class is used to
traverse the grid and alter the values of squares.

I am always looking for ways to improve this project so please feel free to share any different
approaches!
