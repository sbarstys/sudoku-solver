/*This program uses my own implementation of the backtracking
algorithm described in this wikipedia article:
https://en.wikipedia.org/wiki/Sudoku_solving_algorithms 
*/
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <utility>

const int ROW_FACTOR = 9;
const int CONNECT_NUM_ROWS = 9;
const int RP_MARK_I = 0;
const int RP_MARK_II = 3;
const int RP_MARK_III = 6;
const int EXHAUSTED = 10;

class Grid {
    private:
        struct Node {
            Node() {}

            Node(int datum_in, Node * top_in, Node * bottom_in,
             Node * left_in, Node * right_in)
            : datum(datum_in), top(top_in), bottom(bottom_in),
             left(left_in), right(right_in) {}

            int datum;
            Node * top;
            Node * bottom;
            Node * left;
            Node * right;
        };
        void push_back(int & datum_in, bool &start_row);
        void connect_rows();
        std::vector<Node *> row_ptrs;
        Node * bottom_right;
    public:
        void make_grid(std::ifstream &in_file);
        void print_grid();
        void output_to_file(std::ofstream &out_file);
        void solve();
        
        ~Grid();
        
        class Iterator {
            friend class Grid;
            public:
                Iterator();
                Iterator(Node * node_in);
                Iterator& operator++();
                Iterator& operator--();
                Iterator& up();
                Iterator& down();
                bool r_safe();
                bool l_safe();
                int operator*();
                bool operator==(Iterator rhs);
                bool operator!=(Iterator rhs);
                void fill_value(int new_datum);
                bool get_direction();
                void change_direction();
            private:
                Node * node_ptr;
                bool direction;
        };
        Iterator begin(const int row);       
        Iterator end();

    private:
        std::vector<Iterator> empty_nodes;
        bool check_row(Iterator &iter);
        bool check_col(Iterator &iter);
        bool check_box(Iterator &iter);
        void determine_box_row(Grid::Iterator &iter);
        bool scan_box_row(Iterator &iter, Iterator &original);
        std::pair<bool, bool> move_around_box(Iterator &iter, Iterator &orig);
        void move_iterator(Iterator &iter);
        void make_empty_cell_list();
};

