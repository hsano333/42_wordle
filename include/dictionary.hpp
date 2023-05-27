#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <vector>
#include <string>

class Dictionary
{
    public:
        //Dictionary(char *filepath);
        //~Dictionary();
        static void load_dictionary(char *filepath);
        static std::string get_word();
        static size_t get_size();
        static bool exist(std::string& word);
    private:
        //static char *path;
        static std::vector<std::string> words;

};
#endif
