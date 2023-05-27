#include "wordle.hpp"
#include "dictionary.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

std::vector<std::string> Dictionary::words;

int main(int argc, char** argv)
{
    //int test = getchar();
    //printf("test getchar:%d\n", test);
    srand(time(NULL));
    if (argc != 2){
        cout << "Please specify a dictionary file" << endl;
        exit(1);
    }
    try{
        Dictionary::load_dictionary(argv[1]);
        Wordle game;
        while(1)
        {
            string word = Dictionary::get_word();
            if (CHEAT){
                printw("word:%s\n" , word.c_str());
            }
            game.play(word);
            game.board.reset();
        }
    }catch (std::exception &e){
        cout << "Invalid dictionary file" << endl;
        exit(1);
    }
    return (0);
}
