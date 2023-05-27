#include "dictionary.hpp"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <algorithm>
#include <ctype.h>
#include <random>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
Dictionary::Dictionary(char *filepath) : path(filepath)
{
    Dictionary::load_dictionary();
}

Dictionary::~Dictionary()
{
    ;
}
*/

static bool is_alphabet(const string &str)
{
    auto it = std::find_if(str.begin(), str.end(), [](char c){ return !(islower(c) || isupper(c));});
    if (it != str.end()){
        return (true);
    }
    return (false);

}

void Dictionary::load_dictionary(char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0){
        cout << strerror(errno) << endl;
        throw std::exception();
    }
    int fd_cin_bk = dup(0);
    dup2(0, fd_cin_bk);
    string word;
    dup2(fd, 0);
    while(std::getline(std::cin, word)) {
        if (word.size() != 5 || is_alphabet(word)){
            throw std::exception();
        }
        transform (word.begin(), word.end(), word.begin(), tolower);
        words.push_back(word);
    }
    dup2(fd_cin_bk, 0);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    close(fd);
}

string Dictionary::get_word()
{
    // size_t i = (((double)rand())/RAND_MAX) * words.size();
    std::random_device seed;
    std::mt19937 engine(seed());
    size_t i = engine() % words.size();
    return (words[i]);
}

size_t Dictionary::get_size()
{
    return (words.size());
}

bool Dictionary::exist(std::string& word)
{
    return (find(words.begin(), words.end(), word) != words.end());
}
