/*This program uses my own implementation of the backtracking
algorithm described in this wikipedia article:
https://en.wikipedia.org/wiki/Sudoku_solving_algorithms 
*/
#include "grid.h"

Grid::Iterator Grid::begin(const int row) {
    return Grid::Iterator(row_ptrs[row]);
}
        
Grid::Iterator Grid::end() {
    return Grid::Iterator();
}

Grid::Iterator::Iterator() 
: node_ptr(nullptr), direction(true) {}

Grid::Iterator::Iterator(Node * node_in) 
: node_ptr(node_in), direction(true) {}

Grid::Iterator& Grid::Iterator::operator++() {
    assert(node_ptr);
    node_ptr = node_ptr->right;
    return *this;          
}

Grid::Iterator& Grid::Iterator::operator--() {
    assert(node_ptr);
    node_ptr = node_ptr->left;
    return *this;      
}

Grid::Iterator& Grid::Iterator::up() {
    assert(node_ptr);
    node_ptr = node_ptr->top;
    return *this;      
}

Grid::Iterator& Grid::Iterator::down() {
    assert(node_ptr);
    node_ptr = node_ptr->bottom;
    return *this;      
}

//Check if the space to the right of the iterator is valid
bool Grid::Iterator::r_safe() {
    assert(node_ptr);
    return node_ptr->right != nullptr;
}

//Check if the space to the left of the iterator is valid
bool Grid::Iterator::l_safe() {
    assert(node_ptr);
    return node_ptr->left != nullptr;
}

int Grid::Iterator::operator*() {
    assert(node_ptr);
    return node_ptr->datum;
}

bool Grid::Iterator::operator==(Iterator rhs) {
    return  node_ptr == rhs.node_ptr;
}

bool Grid::Iterator::operator!=(Iterator rhs) {
    return  node_ptr != rhs.node_ptr;
}
             
void Grid::Iterator::fill_value(int new_datum) {
   assert(node_ptr);
    node_ptr->datum = new_datum;
}

bool Grid::Iterator::get_direction(){
    return direction;
}

//Switch the direction of the iterator. Right = true. Left = false.
void Grid::Iterator::change_direction() {
    direction = !direction;
}