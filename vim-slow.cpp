// O(N^3)

#include <iostream>
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
	int from = pos[efrom] + 1;
	vector<int> directdist(N, INF);
	vector<int> active(ALPHA, 2);
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

	int ret = INF;
	for (int i = efirstUncovered; i < eend; ++i) {
		ret = min(ret, dist[eat][i] + pos[i] - pos[efirstUncovered] + solve(efirstUncovered, i+1));
	}
	return out = ret;
}

int main() {
	int res = 0;
	getline(cin, line);
	while (line[res] == 'e')
		++res;
	line = line.substr(res);
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
	res += eend - 1; // all the "x", except for the fake one
	cout << res << endl;
	return 0;
}
