#include <iostream>
#include <sstream>
#include "md5.h"

using std::cout; using std::endl;

int main(int argc, char *argv[]) {

	int iterator = 0;
	std::string str, iter, hashed;

	std::stringstream ss;

	while (true) {
		ss << iterator++;
		iter.assign(ss.str());

		str.assign("abbhdwsy" + iter);
		hashed = md5(str);
		if (hashed.substr(0, 5) == "00000") {
			cout << "pos " << hashed[5] << ": " << hashed[6] << std::endl;
		}
		ss.str(std::string());
	}
	return 0;
}
