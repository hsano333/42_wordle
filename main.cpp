#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

#define DEFAULT_FILE (char *)"words.txt"

#define YELLOW(c) std::cout << "\x1b[43m\x1b[30m" << c << "\x1b[49m\x1b[39m"
#define GREEN(c)  std::cout << "\x1b[42m\x1b[30m" << c << "\x1b[49m\x1b[39m"
#define GREY(c)   std::cout << "\x1b[47m\x1b[30m" << c << "\x1b[49m\x1b[39m"


std::vector<std::string> words;
std::vector<std::string> inputs;

void get_words(char *file_path)
{
	std::ifstream ifs(file_path);
	std::string input;

	if (!ifs) {
		std::cerr << "failed: open file." << std::endl;
		exit(1);
	}
	while (getline(ifs, input)) {
		if (input.length() != 5) {
			std::cerr << "word list error" << std::endl;
			exit(1);
		}
		transform(input.begin(), input.end(), input.begin(), toupper);
		words.push_back(input);
	}
	sort(words.begin(), words.end());
}

std::string decide_answer(void) {
	std::random_device seed;
	std::mt19937 mt(seed());
	return words[mt() % words.size()];
}

bool is_currect_input(std::string input) {
	for (size_t i = 0; i < input.length(); i++) {
		if (!isalpha(input.at(i))) {
			return false;
		}
	}
	return true;
}

std::string prompt(void) {
	std::string input;
	bool is_correct_input = false;
	while (!is_correct_input) {
		std::cout << "input: ";
		if(!getline(std::cin, input)) {
			std::cerr << "\nerror" << std::endl;
			exit(1);
		}
		if (input.length() < 1) {
			continue;
		}
		if (!is_currect_input(input)) {
			std::cerr << "input contain inavle character" << std::endl;
			continue;
		}
		if (5 < input.length()) {
			std::cerr << "input too long" << std::endl;
			continue;
		}
		is_correct_input = true;
	}
	transform(input.begin(), input.end(), input.begin(), toupper);
	return input;
}

bool is_include(std::string answer, char input_char) {
	for (size_t i = 0; i < answer.length(); i++) {
		if (answer.at(i) == input_char) {
			return true;
		}
	}
	return false;
}

void print_with_coloring(std::string answer, std::string input) {
	for (size_t i = 0; i < 5; i++) {
		if (i < input.length()) {
			if (answer.at(i) == input.at(i)) {
				GREEN(input.at(i));
			} else if (is_include(answer, input.at(i))) {
				YELLOW(input.at(i));
			} else {
				GREY(input.at(i));
			}
		} else {
			GREY('_');
		}
		std::cout << " ";
	}
	return ;
}


void output_result(std::string answer)
{
	for (size_t i = 0; i < 6; i++) {
		std::cout << "\t";
		if (i < inputs.size()) {
			print_with_coloring(answer, inputs[i]);
		} else {
			std::cout << "_ _ _ _ _";
		}
		std::cout << "\n" << std::endl;
	}
}

int main(int argc, char **argv) {
	try {
		char *file_path;
		if (argc == 2) {
			file_path = argv[1];
		} else {
			file_path = DEFAULT_FILE;
		}
		get_words(file_path);
		std::string answer = decide_answer();
		std::cout << answer << std::endl;
		std::string input;
		int guess_count = 1;
		for (size_t i = 0; i < 6; i++) {
			inputs.push_back(prompt());
			output_result(answer);
			if (answer == inputs[inputs.size() - 1]) {
				break;
			}
			guess_count++;
		}
		if (guess_count <= 6) {
			std::cout << "Congratulations you find the word " << answer << " in " << guess_count << " guesses" << std::endl;
		} else {
			std::cout << "You didn't find the word " << answer << " within 6 guesses:(\n";
			std::cout << "Try again!" << std::endl;
		}
	} catch (...) {
		std::cerr << "Error: " << std::endl;
		return 1;
	}

	return 0;
}
