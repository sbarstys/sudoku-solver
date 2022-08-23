/*This program uses my own implementation of the backtracking
algorithm described in this wikipedia article:
https://en.wikipedia.org/wiki/Sudoku_solving_algorithms 
*/
#include "grid.h"

static bool check_found(Grid::Iterator &current, Grid::Iterator &compare);

//Function that controls the backtracking algorithm and fills the cells
void Grid::solve() {
    make_empty_cell_list();
    auto list_iter = empty_nodes.begin();
    bool check_next;
    int test_value;
    while(list_iter != empty_nodes.end()) {
        check_next = true;
        test_value = *(*list_iter) + 1;
        while(test_value != EXHAUSTED && check_next) {
            list_iter->fill_value(test_value);
            if(!check_row(*list_iter) || !check_col(*list_iter) 
            || !check_box(*list_iter)) {
                ++test_value;            
            }
            else {
                check_next = false;
            }  
        }
        if(!check_next){
            ++list_iter;
        }
        else {
            list_iter->fill_value(0);
            --list_iter; 
        }
    }
}

//Determine if there are any unallowed cells in the row
bool Grid::check_row(Grid::Iterator &iter) {
    auto forward = iter;
    auto backward = iter;
    ++forward;
    --backward;
    for(; forward != end(); ++forward) {
        if(*forward == *iter) {
            return false;
        }
    }
    for(; backward != end(); --backward) {
        if(*backward == *iter) {
            return false;
        }
    }
    return true;
}

//Determine if there are any unallowed cells in the column
bool Grid::check_col(Grid::Iterator &iter) {
    auto go_up = iter;
    auto go_down = iter;
    go_up.up();
    go_down.down();
    for(; go_up != end(); go_up.up()) {
        if(*go_up == *iter) {
            return false;
        }
    }
    for(; go_down != end(); go_down.down()) {
        if(*go_down == *iter) {
            return false;
        }
    }
    return true;
}

//Determine if there are any unallowed cells in the box
bool Grid::check_box(Grid::Iterator &iter) {
    auto row_iter = iter;
    determine_box_row(row_iter);
    return scan_box_row(row_iter, iter);
}

//Determine the row of the top left corner iterator of the box
void Grid::determine_box_row(Grid::Iterator &iter) {
    while(iter.l_safe()) {
        --iter;
    }
    Iterator rp_iter_i(row_ptrs[RP_MARK_I]);
    Iterator rp_iter_ii(row_ptrs[RP_MARK_II]);
    Iterator rp_iter_iii(row_ptrs[RP_MARK_III]);
    while(!(iter == rp_iter_i || iter == rp_iter_ii
            || iter == rp_iter_iii)) {
        iter.up();
    }
}

/*Separate the iterator where there is an iterator in the top left 
corner of each box. Search each box.*/
bool Grid::scan_box_row(Grid::Iterator &iter, Grid::Iterator &orig) {
    auto iter_copy = iter;
    auto iter_copy_boxes = iter;
    auto second_box = ++++++iter_copy_boxes; 
    auto third_box = ++++++iter_copy_boxes;
    auto first_outcome = move_around_box(iter_copy, orig);
    auto second_outcome = move_around_box(second_box, orig);
    auto third_outcome = move_around_box(third_box, orig);
    if(first_outcome.first) {
        return !first_outcome.second;
    }
    else if(second_outcome.first) {
        return !second_outcome.second;
    }
    else {
        return !third_outcome.second;
    }

}

/*Spirals around the box of the original iterator. Returns a pair
whose first element is if we found the original iterator and whose 
second is if there are any unallowed cells*/
std::pair<bool, bool> Grid::move_around_box(Grid::Iterator &iter, 
Grid::Iterator &orig) {
    bool found = false;
    bool incorrect = false;
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    ++iter;
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    ++iter;
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    iter.down();
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    iter.down();
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    --iter;
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    --iter;
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    iter.up();
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    ++iter;
    if(!found) {found = check_found(iter, orig);}
    if(!check_found(iter, orig) && *iter == *orig) {incorrect = true;}

    return {found, incorrect};
}

/*Determine if the iterator traversing the box is at the same location
as the original iterator*/
static bool check_found(Grid::Iterator &current, Grid::Iterator &compare) {
    return current == compare;
}

/*Moves the iterator around the grid in a snake-like
pattern*/
void Grid::move_iterator(Grid::Iterator &iter) {
    if(iter.r_safe() && iter.get_direction()) { 
        ++iter; 
    }
    else if(iter.l_safe() && !iter.get_direction()) { 
        --iter; 
    }
    else { 
        iter.down();
        iter.change_direction();
    } 
}