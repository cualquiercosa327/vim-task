#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
using namespace std;

bool maybeEqualE(char a, char b) {
	return (a == 'e' && b == 'e') && (rand() % 10 != 1);
}

int main(int argc, char** argv) {
	if (argc != 3) {
		cerr << "Syntax: " << *argv << " <N> <seed>" << endl;
		return 1;
	}
	int N = atoi(argv[1]);
	int seed = atoi(argv[2]);

	srand(seed);
	string out;
	vector<char> chr;
	chr.push_back('a');
	chr.push_back('b');
	chr.push_back('c');
	chr.push_back('d');
	chr.push_back('f');
	for (int i = 0; i < 2*N-1; ++i) {
		for (int i = 0; i < rand()%4; ++i) {
			int k = rand() % 3;
			char c = chr[rand() % chr.size()];
			for (int j = 0; j < k; ++j)
				out += c;
		}
		if (rand() % 3 == 0) {
			chr[rand() % chr.size()] = (char)('a' + (rand() % 26));
		}
		out += 'e';
	}
	out.erase(unique(out.begin(), out.end(), maybeEqualE), out.end());
	out.resize(N-1);
	out += 'a';
	cout << out << endl;
}
