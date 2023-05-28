#include "board.hpp"
#include "main.hpp"
#include "dictionary.hpp"
#include <iostream>
#include <string>

#include <vector>

using std::cout;
using std::endl;

Board::Board() : cur_col(0), cur_row(0)
{
    //memset(this->board, 0, sizeof(t_cell) * (B_ROW * B_COL));
    this->reset();
}
Board::~Board()
{
}

int Board::get_color(int col, int row)
{
    return (this->board[col][row].color);
}

char Board::get_char(int col, int row)
{
    return (toupper(this->board[col][row].c));
}

std::string Board::get_line_word(int col)
{
    std::string word = "";
    for(size_t i=0;i<B_ROW;i++){
        if (this->board[col][i].c != ' '){
            word += this->board[col][i].c;
        }
    }
    return (word);
}

void Board::input(char c)
{
    int row = this->cur_row;
    int col = this->cur_col;
    if (col >= B_COL){
        return ;
    }

    if ((c == BS || c == BS2) && row > 0 && row <= B_ROW){
        this->board[col][row-1].c = ' ';
        this->cur_row--;
        return ;
    }
    if (row >= B_ROW){
        return;
    }
    if(this->board[col][row].c == ' ' && (isupper(c) || islower(c))){
        this->board[col][row].c = c;
        this->cur_row++;
    }
}

void Board::input(std::string &input_word)
{
    if (this->cur_col >= B_COL){
        return;
    }
    for(size_t i=0;i<B_ROW;i++){
        this->board[this->cur_col][i].c = input_word[i];
    }
}

bool Board::enter(std::string &target_word)
{
    int cnt = 0;
    std::vector<bool> is_use_char(B_ROW, false);
    std::string line_word = this->get_line_word(this->cur_col);
    //if (!Dictionary::exist(line_word)){
        //return (false);
    //}
    for(size_t i=0;i<B_ROW;i++){
        if (line_word[i] == target_word[i]){
            this->board[this->cur_col][i].color = 5;
            is_use_char[i] = true;
            cnt++;
        } else {
            this->board[this->cur_col][i].color = 0;
        }
    }
    for (size_t i = 0; i < B_ROW; i++) {
        if (this->board[this->cur_col][i].color == 0)
        {
            for (size_t j = 0; j < B_ROW; j++) {
                if(line_word[i] == target_word[j] && is_use_char[j] == false) {
                    this->board[this->cur_col][i].color = 16;
                    is_use_char[j] = true;
                    break;  
                } else if (j == B_ROW - 1 && this->board[this->cur_col][i].color == 0) {
                    this->board[this->cur_col][i].color = 17;
                }
            }
        }
    }
    
    this->cur_col++;
    this->cur_row = 0;
    return (target_word == line_word);
}

void Board::reset()
{
    for(size_t j=0;j<B_COL;j++){
        for(size_t i=0;i<B_COL;i++){
            this->board[j][i].c = ' ';
            this->board[j][i].color = 1;
        }
    }
    this->cur_col = 0;
    this->cur_row = 0;

}

bool Board::filled()
{
    return (cur_col >= B_COL);
}

bool Board::line_filled()
{
    return (cur_row >= 1);
}

int Board::get_line()
{
    return (cur_col);
}
