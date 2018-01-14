#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <list>
//#include <ctype.h>


bool pixels[6][50] = { false };
std::string::size_type sz;   // alias of size_t

std::list<std::string> word_split(std::string s) {
	std::string::size_type sz;   // alias of size_t

	std::list<std::string> c;
	std::regex words_regex("[^\\s]+");
	auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		c.push_back(match_str);
	}
	return c;
}

void rect(std::string s) {
	int xindex = 0, x = 0, y = 0;
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) { 
			xindex = i;
		}
	}
	x = std::stoi(s.substr(0, xindex), &sz);
	y = std::stoi(s.substr(xindex + 1), &sz);

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			pixels[i][j] = true;
		}
	}
	return;
}

void rotateRow(int row, int steps) {
	bool tmp;

	for (int i = 0; i < steps; i++) {
		tmp = pixels[row][49];
		for (int col = 49; col > 0; col--) {
			pixels[row][col] = pixels[row][col - 1];
		}
		pixels[row][0] = tmp;
	}
	return;
}

void rotateColumn(int col, int steps) {
	bool tmp;

	for (int i = 0; i < steps; i++) {
		tmp = pixels[5][col];
		for (int row = 5; row > 0; row--) {
			pixels[row][col] = pixels[row - 1][col];
		}
		pixels[0][col] = tmp;
	}
	return;
}

void rotate(std::string s, std::string t) {
	int rc = 0;
	rc = std::stoi(s.substr(2), &sz);
	if (s[0] == 'y') {
		rotateRow(rc, std::stoi(t, &sz));
	}
	else if (s[0] == 'x') {
		rotateColumn(rc, std::stoi(t, &sz));
	}
	return;
}

void main(void) {
	int count = 0;
	std::string str;
	std::list<std::string> words;
	std::ifstream in;    // Create an input file stream.
	in.open("data.txt");  // Use it to read from a file named data.txt.
	
	while (true) {
		str.clear();
		getline(in, str);
		if (!in) { break; }
		words = word_split(str);

		if (words.size() == 2) {
			rect(words.back());
		}
		else if (words.size() == 5) {
			words.pop_front();
			words.pop_front();
			rotate(words.front(), words.back());
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 50; j++) {
			if (pixels[i][j]) {
				std::cout << 'x';
				count++;
			}
			else {
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
	std::cout << "\nlit pixels: " << count;
	return;
}