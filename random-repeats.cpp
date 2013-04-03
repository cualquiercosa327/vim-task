#include <iostream>
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
	for (int i = 0; i < N-1; ++i) {
		for (int i = 0; i < rand()%4; ++i) {
			int k = rand() % 3;
			char c = (char)('a' + (rand() % 5));
			for (int j = 0; j < k; ++j)
				out += c;
		}
		out += 'e';
	}
	out += 'a';
	out.erase(unique(out.begin(), out.end(), maybeEqualE), out.end());
	cout << out << endl;
}
