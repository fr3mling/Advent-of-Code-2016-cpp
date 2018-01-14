/* fgets example */
#include <stdio.h>
#include <string>
#include <regex>
#include <list>
#include <iostream>

void sort(int *a, int *b) {
	int tmp;
	if (*a > *b) {
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

int Parser(char * mystring, std::list<int> *l)
{
	std::string::size_type sz;   // alias of size_t

	const std::string s = mystring;

	std::regex words_regex("[^\\s]+");
	auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		int hej = stoi(match_str, &sz);
		l->push_back(hej);
	}
	return 0;
}


int main()
{
	std::list<int> l;
	std::string::size_type sz;
	FILE * pFile;
	char mystring[17], mystring2[17], mystring3[17];
	int possible = 0;
	int a[3], b[3], c[3];

	pFile = fopen("file.txt", "r");
	if (pFile == NULL) perror("Error opening file");
	else {
		while (fgets(mystring, 17, pFile) != NULL) {
			fgets(mystring2, 17, pFile);
			fgets(mystring3, 17, pFile);
			//Dela upp sträng i tre "ord" och
			//Casta "orden" till intar.
			Parser(mystring, &l);
			//l.sort();
			a[0] = l.front();
			l.pop_front();
			a[1] = l.front();
			l.pop_front();
			a[2] = l.front();
			l.pop_front();

			Parser(mystring2, &l);
			//l.sort();
			b[0] = l.front();
			l.pop_front();
			b[1] = l.front();
			l.pop_front();
			b[2] = l.front();
			l.pop_front();

			Parser(mystring3, &l);
			//l.sort();
			c[0] = l.front();
			l.pop_front();
			c[1] = l.front();
			l.pop_front();
			c[2] = l.front();
			l.pop_front();
			//(sortera)
			
			//jämför
			for (int i = 0; i < 3; i++) {
				if (a[i] < b[i] + c[i] && b[i] < a[i] + c[i] && c[i] < a[i] + b[i]) possible++;
			}
			//std::cout << possible << "\n";
		}
		fclose(pFile);
	}
	std::cout << possible << "\n";
	return 0;
}