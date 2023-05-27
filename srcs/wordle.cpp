#include "wordle.hpp"
#include "main.hpp"
#include "dictionary.hpp"
#include <iostream>
#include <string>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;


static WINDOW* init_ncurses();
Wordle::Wordle() : win(NULL)
{
    this->win = init_ncurses();
}

Wordle::~Wordle()
{
    //free(this->win);
	endwin();
}

void	init_color_pair(void)
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(9, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(10, COLOR_BLUE, COLOR_GREEN);
	init_pair(11, COLOR_RED, COLOR_BLUE);
	init_pair(12, COLOR_YELLOW, COLOR_RED);
	init_pair(13, COLOR_RED, COLOR_GREEN);
	init_pair(14, COLOR_RED, COLOR_CYAN);
	init_pair(15, COLOR_BLUE, COLOR_WHITE);
	init_pair(16, COLOR_BLACK, COLOR_YELLOW);
	init_pair(17, COLOR_BLACK + 8, COLOR_WHITE);
}

static WINDOW* init_ncurses()
{
	WINDOW *win = initscr();
    if (!win){
        throw std::exception();
    }
    init_color_pair();
    return (win);
}

static void write_header()
{
    printw("\n \
/\\ \\  __/\\ \\                   /\\ \\    /\\_ \\ \n \
\\ \\ \\/\\ \\ \\ \\    ___    _ __   \\_\\ \\   \\//\\ \\       __ \n \
 \\ \\ \\ \\ \\ \\ \\  / __`\\ /\\`'__\\ /'_` \\    \\ \\ \\    /'__`\\ \n \
  \\ \\ \\_/ \\_\\ \\/\\ \\L\\ \\\\ \\ \\/ /\\ \\L\\ \\    \\_\\ \\_ /\\  __/ \n \
   \\ `\\___x___/\\ \\____/ \\ \\_\\ \\ \\___,_\\   /\\____\\\\ \\____\\ \n \
    '\\/__//__/  \\/___/   \\/_/  \\/__,_ /   \\/____/ \\/____/ \n \
            \n");
    printw("Total words available: %zu\n", Dictionary::get_size());
}

void Wordle::render()
{

    write_header();

	attron(COLOR_PAIR(1));
    printw("+");
    for(size_t i=0;i<B_ROW;i++){
        printw("----");
    }
    for(size_t j=0;j<B_COL;j++)
    {
        printw("%c+\n|", BS);
        for(size_t i=0;i<B_ROW;i++){
            if (this->board.get_char(j, i) != ' '){
                attron(COLOR_PAIR(this->board.get_color(j, i)));
            }
            printw(" ");
            printw("%c", this->board.get_char(j, i));
            printw(" ");
            attron(COLOR_PAIR(1));
            printw("|");
        }
        printw("\n");
        printw("+");
        for(size_t i=0;i<B_ROW;i++){
            printw("---+");
        }
    }
    printw("\n");
    refresh();
}

bool invalid_char(char c)
{
    if (islower(c) || isupper(c) || c == BS || c == BS2 || c == CR){
        return (false);
    }
    return (true);
}

#include <unistd.h>
void Wordle::play(std::string word)
{
    int ic;
    char c;
    this->render();
    while(1)
    {
        while(1)
        {
            clear();
            read(0, &ic, 4);
            c = (char)ic;
            if (invalid_char(c)){
                continue;
            }
            c = tolower(c);
            this->board.input(c);
            this->render();
            if (c == CR){
                if(this->board.line_filled()){
                    break;
                }else{
                    printw("\n Error:Blank\n", this->board.get_line());
                    refresh();
                }
            }
        }

        bool result = this->board.enter(word);
        clear();
        this->render();
        if (this->board.filled() || result){
            if (result){
                printw("\nCongratulations you found the word %s in %d guesses \n",word.c_str(),  this->board.get_line());
            }else{
                printw("\nUnfortunately, you coludn't find the word %s \n", word.c_str());
            }
            break;
        }else{
            refresh();
        }
    }
    printw("will you play next game?(y/n)\n");
    refresh();
    read(0, &c, 1);
    while (!(tolower(c) == 'y' || tolower(c) == 'n'))
    {
        read(0, &c, 1);
    }
    clear();
    if (tolower(c) == 'n')
    {
        exit(0);
    }
}

