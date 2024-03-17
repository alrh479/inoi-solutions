#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e5 + 5;
const int L = 19;
int pr[N][L], n, q, h[N], e[N], bala[N], pain[N], ePain[N];
vector<array<int, 2>> adj[N];

void dfs(int v) {
	for (int i = 1; i < L; i++) pr[v][i] = pr[pr[v][i - 1]][i - 1];
	for (auto u: adj[v])  {
		if (u[0] != pr[v][0]) {
			h[u[0]] = h[v] + 1;
			pr[u[0]][0] = v;

			dfs(u[0]);
			e[v] += e[u[0]] + u[1];
		}
		else
			e[v] += u[1];
	}
}
void dfs2(int v) {
	for (auto u: adj[v]) if (u[0] != pr[v][0]) {
		bala[u[0]] = bala[v] + e[u[0]];
		ePain[u[0]] = e[v] - e[u[0]] + ePain[v];
		pain[u[0]] = pain[v] + ePain[u[0]];
		dfs2(u[0]);
	}
}

int lca(int u, int v) {
	if (h[u] > h[v]) swap(u, v);
	while (h[u] < h[v])
		v = pr[v][__lg(h[v] - h[u])];
	if (u == v) return u;
	for (int i = L - 1; i >= 0; i--)
		if (pr[u][i] != pr[v][i])
			u = pr[u][i], v = pr[v][i];
	assert(pr[u][0] == pr[v][0]);
	return pr[u][0];
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;

	for (int i = 1; i < n; i++) {
		int u, v, t; cin >> u >> v >> t; u--, v--;
		adj[u].push_back({v, t});
		adj[v].push_back({u, t});
	}
	dfs(0);
	dfs2(0);
	cout << fixed << setprecision(3);
	while (q--) {
		int s, e; cin >> s >> e; s--, e--;
		int l = lca(s, e);
		int ans = bala[s] - bala[l] + pain[e] - pain[l];
		cout << (long double) ans << '\n';
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
