#include "bits/stdc++.h"
using namespace std;
const int N = 200;
const int M = (N / 16) + 5;
unsigned short n;
bool flag;
vector<array<int, 3>> E;
bitset<2 * N> C;
vector<short> order;
int T[2 * N];

struct bit {
	unsigned int X[M];
	inline void set(short i, bool x) {
		short j = i >> 5;
		if (x) X[j] |= 1 << (i - (j << 5));
		else X[j] &= ~(1 << (i - (j << 5)));
	}
	inline bool get(short i) {
		short j = i >> 5;
		return X[j] >> (i - (j << 5)) & 1;
	}
} A[2 * N], B[2 * N], used;

inline void stat(short v, bool vp, short u, bool up, bool x) {
	A[v << 1 | vp].set(u << 1 | up, x);
	B[u << 1 | up].set(v << 1 | vp, x);
}

void dfs1(short v) {
	used.set(v, 0);
	for (short i = 0; i < M; i++) {
		int t;
		while (t = used.X[i] & A[v].X[i]) {
			short k = __lg(t);
			//assert(used.get((i << 5) + k) && A[v].get((i << 5) + k));
			dfs1((i << 5) + k);
		}
	}
	order.push_back(v);
}
void dfs2(short v) {
	used.set(v, 0);
	if (C[v >> 1]) {
		flag = false;
		return;
	}
	C[v >> 1] = true;
	for (short i = 0; i < M && flag; i++) {
		int t;
		while (t = used.X[i] & B[v].X[i]) {
			short k = __lg(t);
			dfs2((i << 5) + k);
		}
	}
}

bool can() {
	memset(used.X, 0xffffff, sizeof used.X);
	order.clear();
	for (short i = 0; i < 2 * n; i++) if (used.get(i)) dfs1(i);

	memset(used.X, 0xffffff, sizeof used.X);
	flag = true;
	for (short i = order.size() - 1; i >= 0; i--) {
		short v = order[i];
		if (used.get(v)) {
			C = 0;
			dfs2(v);
			if (!flag) return false;
		}
	}
	return true;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	iota(T, T + 2 * n, 0);

	E.reserve(n * (n - 1) / 2);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int w;
			cin >> w;
			E.push_back({w, i, j});
		}
	}
	E.push_back({0, 0, 0});
	E.push_back({0, 0, 0});
	if (n == 1) {
		cout << 0;
		return 0;
	}
	else if (n == 2) {
		cout << 0;
		return 0;
	}

	sort(E.begin(), E.end());

	for (short r = E.size() - 1; r >= 0; r--) {
		stat(E[r][1], 1, E[r][2], 0, 1);
		stat(E[r][2], 1, E[r][1], 0, 1);

		stat(E[r][1], 0, E[r][2], 1, 1);
		stat(E[r][2], 0, E[r][1], 1, 1);
	}

	int ans = E.back()[0];
	short l = -1;
	const short SZ = n * n / 4 + 2;
	bool yes = false;
	for (short r = 0, sz = E.size(); r < E.size(); r++, sz--) {
		stat(E[r][1], 0, E[r][2], 1, 0);
		stat(E[r][2], 0, E[r][1], 1, 0);
		if (!yes) l = r;

		if (sz <= SZ) {
			while (can()) {
				yes = true;
				ans = min(ans, E[l][0] + E[r][0]);
				stat(E[l][1], 1, E[l][2], 0, 1);
				stat(E[l][2], 1, E[l][1], 0, 1);
				l--;
				if (l < 0) break;
			}
			if (l < 0) break;
		}

		if (!yes) {
			stat(E[r][1], 1, E[r][2], 0, 0);
			stat(E[r][2], 1, E[r][1], 0, 0);
		}
	}
	cout << ans;
	return 0;
}
