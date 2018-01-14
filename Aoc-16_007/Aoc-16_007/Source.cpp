#include <string>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <regex>
#include <list>

std::string pop(std::list<std::string> *li) {
	std::string str = li->front();
	li->pop_front();
	return str;
}


std::list<std::string> parser(std::list<std::string> * bracks, std::list<std::string> * nobracks, std::string s) {
	std::string::size_type sz;   // alias of size_t
	std::list<std::string> op;
	bool br = false;

	std::regex words_regex("[\\w]+");
	auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();

		op.push_back(match_str);
		if (br) { bracks->push_back(match_str); br = false; }
		else { nobracks->push_back(match_str); br = true; }
	}
	return op;
}


void main(void) {
	int tls = 0,ssl = 0;
	std::string str, test, jmfr;
	std::list<std::string> li, bracks, nobracks, abas;
	bool bracket = false, abba = false, babba = false, sslb = false;

	std::ifstream in;    // Create an input file stream.
	in.open("data.txt");  // Use it to read from a file named data.txt.
	while (true) {
		str.clear();
		abas.clear();
		sslb = false;
		getline(in, str);
		if (!in) { break; }
		li = parser(&bracks, &nobracks, str);


		while (!nobracks.empty()) {
			test = pop(&nobracks);
			for (int i = 0; i < test.length() - 2; i++) {
				if (test[i] == test[i + 2] && test[i] != test[i + 1]) {
					abas.push_back(test.substr(i, 3));
				}
			}
		}

		while (!bracks.empty()) {
			test = pop(&bracks);
			for (int i = 0; i < test.length() - 2; i++) {
				for (int j = 0; j < abas.size(); j++) {
					jmfr = abas.front();
					jmfr[0] = jmfr[1];
					jmfr[1] = jmfr[2];
					jmfr[2] = jmfr[0];
					if (test.substr(i, 3) == jmfr && !sslb) {
						ssl++;
						sslb = true;
					}
					abas.push_back(abas.front());
					abas.pop_front();
				}
			}
		}
	}




		/*
		
		while (!li.empty()) {
			test = pop(&li);
			if (!bracket && !abba) {
				for (int i = 0; i < test.length() - 3; i++) {
					if (test[i] == test[i + 3] && test[i + 1] == test[i + 2] && test[i] != test[i + 1]) {
						abba = true;
						break;
					}
				}
				bracket = true;
			} else if ( !bracket && abba) { bracket = true; }
			else if (bracket && !babba) {
				for (int i = 0; i < test.length() - 3; i++) {
					if (test[i] == test[i + 3] && test[i + 1] == test[i + 2] && test[i] != test[i + 1]) {
						babba = true;
						break;
					}
				}
				bracket = false;
			} else if (!bracket && babba) { bracket = false; }
		}
		bracket = false;
		if (abba == true && babba == false) {
			tls++;
		}
		abba = babba = false;
	}
	std::cout << tls;*/
}