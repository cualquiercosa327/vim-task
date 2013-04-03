// like vim-slow

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <cassert>
#include <string>
using namespace std;
// using namespace std::tr1;

const int ALPHA = 28, E = 4;

int ctoi(char c) {
	if ('a' <= c && c <= 'z')
		return c - 'a';
	if (c == ' ')
		return 26;
	return 27;
}

char itoc(int c) {
	if (0 <= c && c < 26)
		return (char)('a' + c);
	if (c == 26)
		return ' ';
	if (c == 27)
		return '.';
	assert(false);
}

struct TracedInt {
public:
	int len;
	char before, after;
	shared_ptr<TracedInt> mid, mid2;
	TracedInt() : len(0), before(0), after(0) {}
};

TracedInt INF;

bool operator<(const TracedInt& a, const TracedInt& b) {
	return a.len < b.len;
}

TracedInt operator+(char c, TracedInt v) {
	TracedInt r;
	r.before = c;
	r.mid.reset(new TracedInt(v));
	r.len = v.len + 1;
	return r;
}

TracedInt operator+(TracedInt v, char c) {
	TracedInt r;
	r.mid.reset(new TracedInt(v));
	r.after = c;
	r.len = v.len + 1;
	return r;
}

TracedInt operator+(TracedInt a, TracedInt b) {
	TracedInt r;
	r.mid.reset(new TracedInt(a));
	r.mid2.reset(new TracedInt(b));
	r.len = a.len + b.len;
	return r;
}

void operator+=(TracedInt& v, char c) { v = v + c; }

bool operator==(TracedInt a, TracedInt b) { return a.len == b.len; } // say
bool operator!=(TracedInt a, TracedInt b) { return !(a == b); }

TracedInt ManyH(int n) {
	TracedInt r;
	r.len = n;
	return r;
}

void stringify(TracedInt i, string& out) {
	if (i == INF) {
		out += "<inf>";
		return;
	}
	if (i.before)
		out += i.before;
	if (i.mid)
		stringify(*i.mid, out);
	else if (i.len)
		out += string(i.len, 'h');
	if (i.mid2)
		stringify(*i.mid2, out);
	if (i.after)
		out += i.after;
}

ostream& operator<<(ostream& os, TracedInt i) {
	string s;
	stringify(i, s);
	return os << s << " (" << i.len << ")";
}



string line;
int N;

int eend;
vector<int> pos, invpos;
vector<vector<TracedInt> > dist;


void finddists(int efrom) {
	// start from the position after the "e" (which is where we end up after "x") - this is not an "e"
	int from = pos[efrom] + 1;

	vector<TracedInt> directdist(N, INF);
	vector<TracedInt> active(ALPHA);
	for (int i = 0; i < ALPHA; ++i) {
		active[i] += 'f';
		active[i] += itoc(i);
	}
	for (int pos = from + 1; pos < N; ++pos) {
		int c = ctoi(line[pos]);
		if (c == E)
			continue;
		directdist[pos] = active[c];
		active[c] += 'f';
		active[c] += itoc(c);
		for (int j = 0; j < ALPHA; ++j) {
			if (j == E)
				continue;
			TracedInt copy = active[c];
			copy.after = itoc(j);
			active[j] = min(active[j], copy);
		}
	}
	TracedInt cur = INF;
	for (int pos = N; pos --> from+1; ) {
		cur += 'h';
		cur = min(cur, directdist[pos]);
		if (line[pos] == 'e')
			dist[efrom][invpos[pos]] = cur;
	}
}

vector<vector<TracedInt> > mem;
TracedInt solve(int eat, int efirstUncovered) {
	if (efirstUncovered == eend)
		return TracedInt();
	TracedInt& out = mem[eat][efirstUncovered];
	if (out != INF)
		return out;

	TracedInt ret = INF;
	for (int i = efirstUncovered; i < eend; ++i) {
		ret = min(ret, dist[eat][i] + ManyH(pos[i] - pos[efirstUncovered]) + solve(efirstUncovered, i+1));
	}
	return out = ret;
}

bool equalE(char a, char b) {
	return a == 'e' && b == 'e';
}

int main() {
	INF.len = 1 << 27;
	getline(cin, line);

	assert(line[line.size()-1] != 'e');

	// get rid of initial "e"s
	int firstNonE = 0;
	string initialOutput;
	while (line[firstNonE] == 'e') {
		++firstNonE;
		initialOutput += 'x';
	}
	line = line.substr(firstNonE);

	string origLine = line;
	int origNumE = count(origLine.begin(), origLine.end(), 'e') + firstNonE;

	// get rid of duplicate "e"s, count one "h" for each
	line.erase(unique(line.begin(), line.end(), equalE), line.end());

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
	dist.assign(eend, vector<TracedInt>(eend, INF));
	mem.assign(eend, vector<TracedInt>(eend, INF));

	for (int i = 0; i < eend; ++i) {
		finddists(i);
	}

	TracedInt sol = solve(0, 1);

	// Now, we need to reinsert "h"es, and "x"es, and prepend "output"...
	string output;
	stringify(sol, output);
	int cursor = 0, edel = firstNonE;
	string execCmd = initialOutput;
	for (int i = 0; i < (int)output.size(); ++i) {
		char cmd = output[i];
		execCmd += cmd;
		if (cmd == 'f') {
			cmd = output[++i];
			execCmd += cmd;
			if (cmd == 'e') {
				cerr << "INVALID, find for E" << endl;
				return 1;
			}
			while (cursor < (int)origLine.size() && origLine[cursor] == 'e')
				++cursor;
			string::size_type newp = origLine.find(cmd, cursor + 1);
			if (newp == string::npos) {
				cerr << "INVALID, find out of bounds" << endl;
				return 1;
			}
			cursor = (int)newp;
		}
		else if (cmd == 'h') {
			if (cursor == 0) {
				cerr << "INVALID, H out of bounds" << endl;
				return 1;
			}
			--cursor;
			if (origLine[cursor] == 'e') {
				++edel;
				execCmd += 'x';
				while (cursor > 0 && origLine[cursor-1] == 'e') {
					--cursor;
					++edel;
					execCmd += 'h';
					execCmd += 'x';
				}
			}
		}
	}

	cout << execCmd << endl;
	cout << edel << " deleted out of " << origNumE << endl;
	cout << "length " << execCmd.size() << endl;
	return 0;
}
