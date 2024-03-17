#include "bits/stdc++.h"
#define int long long
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
const long long INF = 1ll << 60;
const int N = 20;
const int M = 1e9 + 7;
vector<vector<array<int, 2>>> adj, G;
int n, m, k, C[N][N];

int pw(int a, int b) {
	int re = 1;
	for (; b; b >>= 1, a = a * a % M) if (b & 1) re = re * a % M;
	return re;
}

int dpr[N];
int gpr(int x) { return dpr[x] == x ? x : dpr[x] = gpr(dpr[x]);}
int merge(int u, int v) {
	u = gpr(u), v = gpr(v);
	if (u == v) return 0;
	dpr[u] = v;
	return 1;
}

int find_mst() {
	iota(dpr, dpr + N, 0);
	vector<array<int, 3>> E;
	FOR(i, 0, n) for (auto p: adj[i]) E.push_back({p[1], i, p[0]});
	sort(E.begin(), E.end());
	int ans = 0;
	for (auto p: E) {
		if (merge(p[1], p[2])) ans += p[0];
	}
	return ans;
}

int solve(int mask) {
	FOR(i, 0, n) if (mask >> i & 1) {
		if (adj[i].size() != 2) return 0;
	}
	FOR(i, 0, n) if (mask >> i & 1) {
		assert(adj[i].size() == 2);
		int u1 = adj[i][0][0];
		int w1 = adj[i][0][1];
		int u2 = adj[i][1][0];
		int w2 = adj[i][1][1];
		if (u1 == u2) continue;
		adj[i].clear();
		adj[u1].erase(find(adj[u1].begin(), adj[u1].end(), array<int, 2>{i, w1}));
		adj[u2].erase(find(adj[u2].begin(), adj[u2].end(), array<int, 2>{i, w2}));
		w1 = max(w1, w2);
		adj[u1].push_back({u2, w1});
		adj[u2].push_back({u1, w1});
	}
	int M = find_mst();
	return M;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	C[0][0] = 1;
	FOR(i, 1, N) {
		C[i][0] = 1;
		FOR(j, 1, i + 1) 
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M;
	}
	cin >> n >> m >> k;
	G.resize(n);
	FOR(i, 0, m) {
		int u, v, w; cin >> u >> v >> w;
		u--, v--;
		G[v].push_back({u, w});
		G[u].push_back({v, w});
	}
	int ans = 0, z = 0;
	FOR(i, 0, n) if (G[i].size() == 2)
		z++;
	z = pw(C[z][k], M - 2);

	FOR(i, 0, 1 << n) if (__builtin_popcount(i) == k) {
		adj = G;	
		ans += solve(i);
	}
	cout << ans * z % M << '\n';
	return 0;
}
//Reading this fills you with DETERMINATION
//13:23:59
