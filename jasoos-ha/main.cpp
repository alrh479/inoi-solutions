#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 3e3 + 5;
const int M = 1e9 + 7;
int C[N][N], ps[N], dp[N][N], sub[N], n, t[N];
vector<array<int, 2>> adj[N];

void dfs(int v, int p, bool rev) {
	sub[v] = 1;
	dp[v][1] = 1;

	for (auto a: adj[v]) if (a[0] != p) {
		int u = a[0];
		bool stat = rev ^ a[1];
		if (!stat) reverse(dp[v] + 1, dp[v] + sub[v] + 1);

		dfs(u, v, rev ^ stat ^ 1);

		for (int i = 1; i < N; i++) {
			ps[i] = ps[i - 1] + dp[u][i];
			if (ps[i] >= M) ps[i] -= M;
		}
		fill(t, t + N, 0);
		for (int x = 1; x <= sub[v]; x++) {
			for (int i = x; i <= x + sub[u]; i++) {
				t[i] += 1ll * ps[i - x] * C[i - 1][x - 1] % M * C[sub[u] + sub[v] - i][sub[v] - x] % M * dp[v][x] % M;
				if (t[i] >= M) t[i] -= M;
			}
		}
		copy(t, t + N, dp[v]);
		sub[v] += sub[u];
		if (!stat)
			reverse(dp[v] + 1, dp[v] + sub[v] + 1);
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v; u--, v--;
		adj[u].push_back({v, 0}); //u < v
		adj[v].push_back({u, 1});
	}

	C[0][0] = 1;
	for (int i = 1; i < N; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			if (C[i][j] >= M) C[i][j] -= M;
		}
	}

	dfs(0, 0, 0);
	cout << accumulate(dp[0], dp[0] + N, 0ll) % M << '\n';


	return 0;
}
//به زآن که فروشند چه خواهند خرید
