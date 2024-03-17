#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e5 + 5;
const int L = 20;
vector<int> adj[N];
int pr[N][L], n, LL[N], U[N], V[N], a[N], sa[N], h[N];

void dfs(int v) {
	for (int i = 1; i < L; i++) pr[v][i] = pr[pr[v][i - 1]][i - 1];

	for (auto u: adj[v]) if (u != pr[v][0]) {
		pr[u][0] = v;
		h[u] = h[v] + 1;
		dfs(u);
	}
}
int lca(int u, int v) {
	if (h[u] > h[v]) swap(u, v);
	while (h[u] < h[v]) v = pr[v][__lg(h[v] - h[u])];
	if (u == v) return u;
	for (int i = L - 1; i >= 0; i--) if (pr[u][i] != pr[v][i]) u = pr[u][i], v = pr[v][i];
	assert(pr[v][0] == pr[u][0]);
	return pr[v][0];
}
void dfs2(int v) {
	for (auto u: adj[v]) if (u != pr[v][0]) {
		sa[u] = a[u] + sa[v];
		dfs2(u);
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	dfs(0);
	for (int i = 1; i < n; i++) {
		cin >> U[i] >> V[i];
		U[i]--, V[i]--;
		LL[i] = lca(U[i], V[i]);
		a[LL[i]]++;
	}
	sa[0] = a[0];
	dfs2(0);
	int ans = 0;
	for (int i = 0; i < n; i++) ans += a[i] * (a[i] - 1) / 2;

	for (int i = 1; i < n; i++) {
		ans += sa[U[i]] + sa[V[i]] - 2 * sa[LL[i]];
	}
	cout << ans << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
