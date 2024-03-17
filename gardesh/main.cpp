#include "bits/stdc++.h"
using namespace std;
const int N = 3e5 + 5;
const int L = 19;
vector<int> T[2][N];
vector<array<int, 3>> Q[N];
int pr[2][L][N], h[2][N], TM = 1, st[N], fn[N], bit[N], n, q, re[N];

void dfs(const int B, int v) {
	for (int i = 1; i < L; i++) pr[B][i][v] = pr[B][i - 1][pr[B][i - 1][v]];
	for (auto u: T[B][v]) if (u != pr[B][0][v]) {
		pr[B][0][u] = v;
		h[B][u] = h[B][v] + 1;
		dfs(B, u);
	}
}

int lca(const int B, int u, int v) {
	if (h[B][u] > h[B][v]) swap(u, v);
	while (h[B][u] < h[B][v]) {
		v = pr[B][__lg(h[B][v] - h[B][u])][v];
	}
	if (u == v) return u;
	for (int i = L - 1; i >= 0; i--) if (pr[B][i][v] != pr[B][i][u]) {
		v = pr[B][i][v];
		u = pr[B][i][u];
	}
	assert(pr[B][0][v] == pr[B][0][u]);
	return pr[B][0][v];
}

inline int dist(const int B, int u, int v) {
	return h[B][u] + h[B][v] - 2 * h[B][lca(B, u, v)];
}
inline bool is_in(const int B, int x, int u, int v) {
	return dist(B, u, x) + dist(B, x, v) == dist(B, u, v);
}

void dfs2(int v, int p) {
	st[v] = TM++;
	for (auto u: T[1][v]) if (u != p) dfs2(u, v);
	fn[v] = TM;
}

inline void add(int x, const int d) {
	for (; x < N; x |= x + 1) bit[x] += d;
}
inline int get(int x) {
	int re = 0;
	for (; x >= 0; x &= (x + 1), x--) re += bit[x];
	return re;
}

void solve(int v, int p) {
	add(st[v], +1);
	add(fn[v], -1);

	for (auto &a: Q[v]) {
		int u = a[0];
		int ind = a[1];
		int co = a[2];
		re[ind] += get(st[u]) * co;
	}

	for (auto u: T[0][v]) if (u != p)
		solve(u, v);

	add(st[v], -1);
	add(fn[v], +1);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	int u, v, a, b;
	for (int j = 0; j < 2; j++) {
		for (int i = 1; i < n; i++) {
			cin >> u >> v; u--, v--;
			T[j][u].push_back(v);
			T[j][v].push_back(u);
		}
	}
	dfs(0, 0);
	dfs(1, 0);

	//a, b dar 0
	//u, v dar 1
	for (int i = 0; i < q; i++) {
		cin >> a >> b >> u >> v;
		u--, v--, a--, b--;
		int L[2] = {lca(1, u, v), lca(0, a, b)};
		Q[a].push_back({u, i, 1});
		Q[b].push_back({u, i, 1});
		Q[a].push_back({v, i, 1});
		Q[b].push_back({v, i, 1});

		Q[a].push_back({L[0], i, -2});
		Q[b].push_back({L[0], i, -2});
		Q[L[1]].push_back({u, i, -2});
		Q[L[1]].push_back({v, i, -2});

		Q[L[1]].push_back({L[0], i, 4});

		if (L[0] == L[1]) {
			re[i]++;
		}
		else {
			re[i] += is_in(1, L[1], u, v);
			re[i] += is_in(0, L[0], a, b);
		}
	}

	dfs2(0, 0);
	solve(0, 0);

	for (int i = 0; i < q; i++) {
		cout << re[i] << '\n';
	}

	return 0;
}
//نرو
