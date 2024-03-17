#include "bits/stdc++.h"
#define int long long
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
const long long INF = 1ll << 60;
const int N = 5e5 + 5;
int pw(int a, int b) {
	int re = 1;
	for (; b; a = a * a % M, b >>= 1) if (b & 1) re = re * a % M;
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

void dfs(int v) {
	for (auto p: adj[v]) {
		int u = p[0], w = p[1];
		if (adj[u].size() > 2 && adj[v].size() == 2) {
			P[ptr].push_back(w);
			ptr++;
		}
		else if (adj[u].size() == 2) {
			P[ptr].push_back(w);
			dfs(u);
		}
	}
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

vector<int> dp(vector<int> &P) {
	for (int i = 0; i < P.size(); i++) {
		for (int j = 0; j < i; j++) {

		}
	}
}

void solve() {
	FOR(i, 0, n) if (adj[i].size() > 2) dfs(i);

	FOR(i, 0, n) if (adj[i].size() == 2) {
		int u1 = adj[i][0][0];
		int u2 = adj[i][1][0];
		if (u1 == u2) continue;
		int w1 = adj[i][0][1];
		int w2 = adj[i][1][1];
		adj[i].clear();
		adj[u1].erase(find(adj[u1].begin(), adj[u1].end(), array<int, 2>{i, w1}));
		adj[u2].erase(find(adj[u2].begin(), adj[u2].end(), array<int, 2>{i, w2}));
		w1 = max(w1, w2);
		adj[u1].push_back({u2, w1});
		adj[u2].push_back({u1, w1});
	}
	int M = find_mst(), W = 0;
	FOR(i, 0, n) for (auto p: adj[i]) W += p[1];

	int cnt = 0;
	FOR(i, 0, ptr) {
		cnt += P[ptr].size();
		dp[i] = hal(P[i]);
		if (i) {
			vector<int> t(dp[i].size() + dp[i - 1].size());
			FOR(j, 0, dp[i].size()) {
				FOR(k, 0, dp[i - 1].size()) {
					t[j + k] += dp[i][j] * dp[i - 1][k] % M;
				}
			}
			dp[i] = t;
		}
	}
	int Q = dp[ptr - 1][cnt - k] * pw(C[cnt - ptr][k], M - 2) % M;
	Q += 2 * M - W;
	cout << Q << '\n';
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
	FOR(i, 0, m) {
		int u, v, w; cin >> u >> v >> w;
		u--, v--;
		adj[v].push_back({u, w});
		adj[u].push_back({v, w});
	}
	solve();
	return 0;
}
//Reading this fills you with DETERMINATION
//13:23:59
