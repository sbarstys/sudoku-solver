/*This program uses my own implementation of the backtracking
algorithm described in this wikipedia article:
https://en.wikipedia.org/wiki/Sudoku_solving_algorithms 
*/
#include "grid.h"

static void run(std::ifstream &in_file);
static void print_opening_header();
static void print_closing_header();

int main(int argc, char * argv[]) {
    if(argc != 2) {
        std::cout << "ERROR: INVALID AMOUNT OF ARGUMENTS\n";
        return 1;
    }
    std::ifstream in_file(argv[1]);
    if(!in_file.is_open()) {
        std::cout << "ERROR OPENING INPUT FILE\n";
        return 1;
    }
    run(in_file);
    return 0;
}

static void run(std::ifstream &in_file) {
    Grid table;
    table.make_grid(in_file);
    print_opening_header();
    table.print_grid();
    table.solve();
    print_closing_header();
    table.print_grid();
}

static void print_opening_header() {
    std::cout << "Unsolved Sudoku puzzle\n";
    std::cout << "----------------------\n";
}

static void print_closing_header() {
    std::cout << "\n";
    std::cout << "Solved Sudoku puzzle\n";
    std::cout << "--------------------\n";
}