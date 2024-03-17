#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e5 + 5;
const int K = 105;
long long dp[N][K], t[N];
int n, k, a[N], leaf[N];
vector<int> adj[N];

void dfs(int v, int p) {
	leaf[v] = adj[v].size() <= 1;
	dp[v][0] = 0;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		fill(t, t + K, -INF);
		for (int i = 0; i <= min(k, leaf[v]); i++) 
			for (int j = 0; j <= leaf[u] && i + j <= k; j++)
				t[i + j] = max(t[i + j], dp[v][i] + dp[u][j]);
		copy(t, t + K, dp[v]);
		leaf[v] += leaf[u];
	}
	dp[v][1] = max(dp[v][1], 1ll * a[v]);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> a[i];

	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 0; i < N; i++) for (int j = 0; j < K; j++) dp[i][j] = -INF;

	dfs(0, 0);
	cout << dp[0][k] << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
