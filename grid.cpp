/*This program uses my own implementation of the backtracking
algorithm described in this wikipedia article:
https://en.wikipedia.org/wiki/Sudoku_solving_algorithms 
*/
#include "grid.h"

static bool get_start_row(int &loop_counter);

Grid::~Grid() {
    for(int i = 0; i < static_cast<int>(row_ptrs.size()); i++) {
        Node * n = row_ptrs[i];
        while(n) {
            Node * to_delete = n;
            n = n->right;
            delete to_delete;
        }
    }
}

//Determines if we need to start a new row
static bool get_start_row(int &loop_counter) {
   return (loop_counter % ROW_FACTOR) == 0;
}

/*This function reads in the the text file
and calls the helper functions needed to make the grid*/
void Grid::make_grid(std::ifstream &in_file) {
    int datum_in;
    int loop_counter = 0;
    bool start_row;
    std::string input_string;
    while(in_file >> input_string) {
        start_row = get_start_row(loop_counter);
        std::istringstream input(input_string);
        while(input >> datum_in) {
            push_back(datum_in, start_row);
            loop_counter++; 
        }
    }
    connect_rows();
}

/*Add the nodes to make the horizontal doubly linked lists
(rows) if a new row needs to be started make a new list.*/
void Grid::push_back(int &datum_in, bool &start_row) {
    if(start_row) { 
        Node * node = new Node{datum_in, nullptr, nullptr, nullptr, nullptr};
        row_ptrs.push_back(node);
        bottom_right = node;
        return;
    }
    Node * node = new Node{datum_in, nullptr, nullptr, bottom_right, nullptr}; 
    bottom_right->right = node;
    bottom_right = node;
}

/*Connect all of the nodes to make vertical doubly linked lists (columns)
thus completing the grid.*/
void Grid::connect_rows() {
    for(int i = 0; i < CONNECT_NUM_ROWS - 1; i++) {
        Node * node_a = row_ptrs[i];
        Node * node_b = row_ptrs[i + 1];
        while(node_a && node_b) {
            node_a->bottom = node_b;
            node_b->top = node_a;
            node_a = node_a->right;
            node_b = node_b->right;
        }
    }
}

//Output grid to terminal
void Grid::print_grid() {
    for(int i = 0; i < static_cast<int>(row_ptrs.size()); i++) {
        Iterator iter(row_ptrs[i]);
        while(iter != end()) {
            std::cout << *iter << " ";
            ++iter;
        }
        std::cout << "\n";
    }
}

/*Find all of the empty cells and store there locations as an iterator
in a vector */
void Grid::make_empty_cell_list() {
    auto iter = begin(0);
    while(iter != end()) {
        if(*iter == 0) {
            auto copy_iter = iter;
            empty_nodes.push_back(copy_iter);
        }
        move_iterator(iter);
    }
}