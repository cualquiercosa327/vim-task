#include <iostream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

typedef unsigned char Alpha;
static const Alpha ALPHA = 28;
static const Alpha E = Alpha('e' - 'a');
Alpha charToAlpha(char c) {
	if ('a' <= c && c <= 'z')
		return Alpha(c - 'a');
	if (c == ' ')
		return 26;
	if (c == '.')
		return 27;
	assert(false);
}

static vector<Alpha> ar;
static int N, lastE = -1;

int solveRightSingleBack(int pos, Alpha pass);
int solveRight(int pos, Alpha pass);
int solve(int pos, Alpha pass1, Alpha pass2, bool ignoreOne = false);

bool anyEAfter(int pos) {
	return pos > lastE;
}

vector<int> cache1, cache2, cache3;
int mhash(int pos, Alpha pass1) { return pos * ALPHA + pass1; }
int mhash(int pos, Alpha pass1, Alpha pass2) { return mhash(pos, pass1) * ALPHA + pass2; }

// includes back
int solveRightSingleBack(int pos, Alpha pass) {
	assert(pass != E);
	if (pos == N)
		return 1 << 29;
	int& mem = cache3[mhash(pos, pass)];
	if (mem >= 0) return mem;

	if (ar[pos] != pass)
		return mem = solveRightSingleBack(pos+1, pass) + 1; // "h"

	// If we have all E's, we must go back. Else go on.
	if (anyEAfter(pos))
		return mem = 1; // "h"

	int res = 1 << 29;
	for (Alpha c = 0; c < ALPHA; ++c) {
		if (c == E)
			continue;
		res = min(res, solveRightSingleBack(pos+1, c) + 3); // "fc", "h"
	}
	return mem = res;
}

// no back
int solveRight(int pos, Alpha pass) {
	assert(pass != E);
	if (pos == N)
		return 1 << 29;
	int& mem = cache2[mhash(pos, pass)];
	if (mem >= 0) return mem;

	if (ar[pos] == E) {
		int base = 0, npos = pos;
		while (ar[npos] == E) {
			++npos;
			++base;
		}
		--base; // last e is accounted for by called functions

		int res = 1 << 29;
		for (Alpha c = 0; c < ALPHA; ++c) {
			if (c == E)
				continue;
			res = min(res, solve(npos, pass, c, true) + 2); // "fc"
		}
		res = min(res, solveRightSingleBack(npos, pass));
		return mem = res + base; // also 'base' many "h"
	}
	else if (ar[pos] == pass) {
		int res = 1 << 29;
		for (Alpha c = 0; c < ALPHA; ++c) {
			if (c == E)
				continue;
			res = min(res, solveRight(pos+1, c) + 2); // "fc"
		}
		return mem = res;
	}
	else {
		return mem = solveRight(pos+1, pass);
	}
}

// includes back
int solve(int pos, Alpha pass1, Alpha pass2, bool ignoreOne) {
	if (pos == N)
		return 1 << 29;
	int dummy = -1;
	int* mem = (ignoreOne ? &dummy : &cache1[mhash(pos, pass1, pass2)]);
	if (*mem >= 0) return *mem;

	if (ar[pos] != pass1) {
		if (ar[pos] != pass2 || ignoreOne) {
			return *mem = solve(pos+1, pass1, pass2) + 1; // "h"
		}
		else {
			int res = 1 << 29;
			for (Alpha c = 0; c < ALPHA; ++c) {
				if (c == E)
					continue;
				res = min(res, solve(pos+1, pass1, c) + 3); // "h", "fc"
			}
			return *mem = res;
		}
	}
	else {
		// Either step back...
		int res = 1 + solveRight(pos, pass2);

		// ... or continue.
		for (Alpha c1 = 0; c1 < ALPHA; ++c1) {
			if (c1 == E)
				continue;

			if (ar[pos] != pass2 || ignoreOne) {
				res = min(res, solve(pos+1, c1, pass2) + 3); // "fc", "h"
			}
			else {
				for (Alpha c2 = 0; c2 < ALPHA; ++c2) {
					if (c2 == E)
						continue;
					res = min(res, solve(pos+1, c1, c2) + 5); // "fc", "h", "fc"
				}
			}
		}
		return *mem = res;
	}
}

int main() {
	string line;
	getline(cin, line);
	N = (int)line.size();
	ar.resize(N);
	for (int i = 0; i < N; ++i)
		ar[i] = charToAlpha(line[i]);

	cache1.assign(N * ALPHA * ALPHA, -1);
	cache2.assign(N * ALPHA, -1);
	cache3.assign(N * ALPHA, -1);

	int res = 0;
	for (int i = 0; i < N; ++i) {
		if (ar[i] == E) {
			++res; // "x"
			lastE = i;
		}
	}
	assert(lastE != N-1);

	int start = 0;
	while (ar[start] == E)
		++start;

	if (start <= lastE)
		res += solveRight(start, charToAlpha(line[start]));

	cout << res << endl;
	return 0;
}
