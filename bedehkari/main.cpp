#include "bits/stdc++.h"
using namespace std;
const int INF = 1 << 29;
const int N = 2e6 + 5;
int d[2 * N], T[N], n, s, t, m;
vector<int> adj[N];
queue<int> Q;

const int BUF_SZ = 1 << 20;
char buf[BUF_SZ];
int pos;
int len;
char next_char() {
	if (pos == len) {
		pos = 0;
		len = (int)fread(buf, 1, BUF_SZ, stdin);
		if (!len) return EOF;
	}
	return buf[pos++];
}
int read_int() {
	int x;
	char ch;
	while (!isdigit(ch = next_char()));
	x = ch ^ 48;
	while (isdigit(ch = next_char())) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x;
}

inline void upd(int x, int dist) {
	if (dist < d[x]) {
		d[x] = dist;
		Q.push(x);
	}
}

int solve() {
	if (T[s] == 0) return -1;
	memset(d, 0x3f, sizeof d);
	s = (s << 1) + (T[s] < 0);
	d[s] = 0;
	Q.push(s);

	while (Q.size()) {
		int v = Q.front();
		int D = d[v];
		Q.pop();

		for (auto u: adj[v >> 1]) {
			if (T[u] < 0) upd(u << 1 | 1, D + 1);
			else {
				if (D + 1 < T[u]) upd(u << 1, D + 1);
				if ((v & 1) || (T[u] != T[v >> 1] - 1 && T[u] < T[v >> 1]))
					upd(u << 1 | 1, max(D, T[u]) + 1);
			}
		}
	}
	int x = min(d[t << 1], d[t << 1 | 1]);
	return x >= INF ? -1 : x;
}

signed main() {
	n = read_int(); m = read_int(); s = read_int(); t = read_int();
	s--, t--;
	for (int i = 0; i < m; i++) {
		int u = read_int(); int v = read_int();
		u--, v--;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	memset(T, -1, sizeof T);

	int k = read_int();
	for (int i = 0; i < k; i++) {
		int u = read_int();
		u--;
		T[u] = i;
	}
	printf("%d\n", solve());
}
