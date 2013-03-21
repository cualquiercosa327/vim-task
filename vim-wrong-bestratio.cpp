// O(N^3)

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <string>
using namespace std;

const int INF = 1 << 29;
const int ALPHA = 28, E = 4;

string line;
int N;

int eend;
vector<int> pos, invpos;
vector<vector<int> > dist;

int ctoi(char c) {
	if ('a' <= c && c <= 'z')
		return c - 'a';
	if (c == ' ')
		return 26;
	return 27;
}

void finddists(int efrom) {
	// start from the position after the "e" (which is where we end up after "x") - this is not an "e"
	int from = pos[efrom] + 1;

	vector<int> directdist(N, INF);
	vector<int> active(ALPHA, 2); // "fc"
	for (int pos = from + 1; pos < N; ++pos) {
		int c = ctoi(line[pos]);
		if (c == E)
			continue;
		directdist[pos] = active[c];
		active[c] += 2;
		for (int j = 0; j < ALPHA; ++j) {
			if (j == E)
				continue;
			active[j] = min(active[j], active[c]);
		}
	}
	int cur = INF;
	for (int pos = N; pos --> from+1; ) {
		++cur; // "h"
		cur = min(cur, directdist[pos]);
		if (line[pos] == 'e')
			dist[efrom][invpos[pos]] = cur;
	}
}

vector<vector<int> > mem;
int solve(int eat, int efirstUncovered) {
	if (efirstUncovered == eend)
		return 0;
	int& out = mem[eat][efirstUncovered];
	if (out != INF)
		return out;

	int ret = INF, counter = 0;
	for (int i = efirstUncovered; i < eend; ++i) {
		int next = dist[eat][i] + pos[i] - pos[efirstUncovered] + solve(efirstUncovered, i+1);
		if (next < ret) {
			ret = next;
			counter = 0;
		}
		else {
			if (++counter == 3) break;
		}
	}
	double bestrat = INF;
	int ret2 = INF;
	counter = 0;
	for (int i = efirstUncovered; i < eend; ++i) {
		double rat = (dist[eat][i] + pos[i] - pos[efirstUncovered]) / (double)(i - efirstUncovered + 1);
		if (rat < bestrat) {
			bestrat = rat;
			int next = dist[eat][i] + pos[i] - pos[efirstUncovered] + solve(efirstUncovered, i+1);
			if (next < ret2) {
				ret2 = next;
				counter = 0;
			}
			else {
				if (++counter == 4) break;
			}
		}
	}
	return out = min(ret, ret2);
}

bool equalE(char a, char b) {
	return a == 'e' && b == 'e';
}

int main() {
	int res = 0;
	getline(cin, line);

	// count all the "x"s
	for (int i = 0; i < (int)line.size(); ++i) {
		if (line[i] == 'e')
			++res;
	}

	// get rid of initial "e"s
	int firstNonE = 0;
	while (line[firstNonE] == 'e')
		++firstNonE;
	line = line.substr(firstNonE);

	// get rid of duplicate "e"s, count one "h" for each
	res += line.size();
	line.erase(unique(line.begin(), line.end(), equalE), line.end());
	res -= line.size();

	line = "e" + line;
	N = (int)line.size();

	invpos.resize(N);
	for (int i = 0; i < (int)line.size(); ++i) {
		if (line[i] == 'e') {
			invpos[i] = (int)pos.size();
			pos.push_back(i);
		}
	}
	eend = (int)pos.size();
	dist.assign(eend, vector<int>(eend, INF));
	mem.assign(eend, vector<int>(eend, INF));

	for (int i = 0; i < eend; ++i) {
		finddists(i);
	}

	res += solve(0, 1);
	cout << res << endl;
	return 0;
}
