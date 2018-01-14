#include <string>
#include <ctype.h>
#include <regex>
#include <iostream>
#include <fstream>


void parser(std::string * name, std::string * chksm, int * ID, std::string s) {
	std::string::size_type sz;   // alias of size_t
	std::string op;

	std::regex words_regex("[\\w]+");
	auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		
		op.append(match_str);
	}
	int sep1 = op.find_first_of("0123456789");
	int sep2 = op.find_last_of("0123456789") + 1;

	name->assign(op, 0, sep1);
	*ID = std::stoi(op.substr(sep1, sep2-sep1));
	chksm->assign(op, sep2);

	return;
}

std::string fran(std::string str) {
	int freqs[26] = { 0 };
	int ind = 0;
	std::string op;

	for (int i = 0; i < str.length(); i++) {
		freqs[(int)str[i] - 97]++;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 26; j++) {
			if (freqs[j] > freqs[ind]) {
				ind = j;
			}
		}
		freqs[ind] = 0;
		op.append(1, (char)(ind+97));
	}
	return op;
}

std::string decipher(std::string str, int ID) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = ((((int)str[i] - 97)+ID)%26)+97;
	}
	return str;
}

void main(void) {
	std::string str, name, chksm, rchksm, deciphered;
	int ID, tot = 0;

	std::ifstream in;    // Create an input file stream.
	in.open("data.txt");  // Use it to read from a file named data.txt.
	while (true) {
		str.clear();
		getline(in, str);
		if (!in) { break; }
		parser(&name, &chksm, &ID, str);
		
		rchksm = fran(name);
		if (chksm == rchksm) {
			deciphered = decipher(name, ID);
			tot += ID;
		}
		if (deciphered[0] == 'n') {
			std::cout << deciphered << " - " << ID << "\n";
		}
	}
}

/*


*/