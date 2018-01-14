#include <string>
#include <iostream>
#include <fstream>


void main(void) {
	int ind = 0;
	std::string str, op;
	int fran[8][26] = { 0 };

	std::ifstream in;    // Create an input file stream.
	in.open("data.txt");  // Use it to read from a file named data.txt.
	while (true) {
		str.clear();
		getline(in, str);
		if (!in) { break; }

		for (int i = 0; i < str.length(); i++) {
			fran[i][(int)str[i] - 97]++;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 26; j++) {
			if (fran[i][j] < fran[i][ind]) {
				ind = j;
			}
		}
		op.append(1, (char)(ind + 97));
		ind = 0;
	}
	std::cout << op;
}