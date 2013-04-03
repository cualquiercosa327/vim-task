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
	string s;
	for (int i = 0; i < 2*N; ++i) {
		if (i % 2 == 1) {
			s += 'e';
		}
		else {
			for (int i = 0; i < rand()%5; ++i)
				s += (char)('a' + (rand() % 26));
		}
	}
	s.resize(N-1);
	s += 'a';
	cout << s << endl;
}
