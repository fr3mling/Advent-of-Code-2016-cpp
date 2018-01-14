#include <regex>
#include <iterator>
#include <iostream>
#include <string>
#include <list>
#include "myLib.h"
#include <math.h>

using namespace std;

int Parser(std::list<char> *c, std::list<int> *l)
{
	std::string::size_type sz;   // alias of size_t

	const std::string s = "R2, L1, R2, R1, R1, L3, R3, L5, L5, L2, L1, R4, R1, R3, L5, L5, R3, L4, L4, R5, R4, R3, L1, L2, R5, R4, L2, R1, R4, R4, L2, L1, L1, R190, R3, L4, R52, R5, R3, L5, R3, R2, R1, L5, L5, L4, R2, L3, R3, L1, L3, R5, L3, L4, R3, R77, R3, L2, R189, R4, R2, L2, R2, L1, R5, R4, R4, R2, L2, L2, L5, L1, R1, R2, L3, L4, L5, R1, L1, L2, L2, R2, L3, R3, L4, L1, L5, L4, L4, R3, R5, L2, R4, R5, R3, L2, L2, L4, L2, R2, L5, L4, R3, R1, L2, R2, R4, L1, L4, L4, L2, R2, L4, L1, L1, R4, L1, L3, L2, L2, L5, R5, R2, R5, L1, L5, R2, R4, R4, L2, R5, L5, R5, R5, L4, R2, R1, R1, R3, L3, L3, L4, L3, L2, L2, L2, R2, L1, L3, R2, R5, R5, L4, R3, L3, L4, R2, L5, R5,";

	std::regex words_regex("[^\\s]+");
	auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		c->push_back(match_str[0]);
		int hej = stoi(match_str.substr(1, match_str.length() - 1), &sz);
		l->push_back(hej);
	}
	return 0;
}



void main(void) {
	int hej = 1;
	char dir = ' ';
	int steps = 0;
	float angle = 0, turn = 0;
	int lookX = 0, lookY = 0, posX = 0, posY = 0, idir = 0;
	bool found = false;

	list<char> c;
	list<int> l;

	list<XY> prevPos;
	XY look = { 0, 0 };
	XY pos = { 0,0 };

	Parser(&c, &l);

	while(c.size() != 0) {
		steps = l.front();
		dir = c.front();

		idir = ((int)dir - 79) / -3;	//'L'=76 ->  1, 'R'=82 -> -1
		turn = idir * My_PI2;			//Multiply by PI/2

		angle = fmod((angle + turn), My_2PI);

		look.x = sin(angle);
		look.y = cos(angle);


		for (int i = 0; i < steps; i++) {
			prevPos.push_back(pos);
			pos.x = pos.x + look.x;
			pos.y = pos.y + look.y;

			for (XY prev : prevPos) {
				if (prev.x == pos.x && prev.y == pos.y && found == false) {
					cout << "First visited twice: [" << pos.x << ',' << pos.y << ']' << '\n'
						 << "Distance: " << abs(pos.x) + abs(pos.y) << "\n\n";
					found = true;
					break;
				}
			}
		}		

		c.pop_front();
		l.pop_front();
	}
	cout << "End of Trail: [" << pos.x << ',' << pos.y << ']' << '\n'
		 << "Distance: " << abs(pos.x) + abs(pos.y) << '\n';
	cout << (int)'L' << ' ' << (int)'R' << ' ' << (int)'D' << ' ' << (int)'U' << '\n';
	system("PAUSE");
}