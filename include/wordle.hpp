#ifndef WORDLE_HPP
#define WORDLE_HPP

#include <ncurses.h>
#include <string>
#include <vector>
#include "board.hpp"

class Wordle
{
    public:
        Wordle();
        ~Wordle();
        void play(std::string word);
        Board board;
    private:
        WINDOW		*win;
        void render();
        void render(const char *input_word);
};
#endif
