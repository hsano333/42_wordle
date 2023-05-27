#ifndef BOARD_HPP
#define BOARD_HPP
#include "main.hpp"
#include <string>

typedef struct cell
{
    char c;
    int color;
    //bool blank;
}   t_cell;

class Board
{
    public:
        Board();
        ~Board();
        int get_color(int col, int row);
        char get_char(int col, int row);
        std::string get_line_word(int col);
        //void input(const char *word);
        void input(char c);
        void input(std::string &word);
        bool enter(std::string &target_word);
        bool filled();
        bool line_filled();
        void reset();
        int get_line();
    private:
        int cur_col;
        int cur_row;
        t_cell board[B_COL][B_ROW];
};
#endif
