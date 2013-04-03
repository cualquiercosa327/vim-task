#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {
	if (argc != 3) {
		cerr << "Syntax: " << *argv << " <N> <seed>" << endl;
		return 1;
	}
	int N = atoi(argv[1]);
	int seed = atoi(argv[2]);

	srand(seed);
	for (int i = 0; i < N; ++i) {
		if (i % 2 && i < N-1) {
			cout << 'e';
		}
		else {
			char c = (char)('a' + (rand() % 25));
			if (c >= 'e') ++c;
			cout << c;
		}
	}
	cout << endl;
}
