#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 1000 + 50;
const int K = 11 + 1;

int ones[N], dp[1 << K][N], n, m, k;
vector<array<int, 2>> adj[N];

void solve_for(int mask) {
	set<pair<int, int>> S;
	for (int i = 0; i < n; i++) {
		int o = ones[i] & mask;
		if (o == mask || !o) continue;
		dp[mask][i] = min(dp[mask][i], max(dp[o][i], dp[o ^ mask][i]));
		S.insert({dp[mask][i], i});
	}
	while (S.size()) {
		int v = S.begin()->second;
		S.erase(S.begin());

		for (auto a: adj[v]) {
			int u = a[0];
			int w = a[1] + dp[mask][v];
			if (w < dp[mask][u]) {
				S.erase({dp[mask][u], u});
				dp[mask][u] = w;
				S.insert({dp[mask][u], u});
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	memset(dp, 0x3F3F3F3F, sizeof dp);
	cin >> k >> n >> m;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			char t;
			cin >> t;
			ones[j] |= (t - '0') * (1 << i);
		}
	}
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	k = (1 << k);
	for (int i = 1; i < k; i++) {
		if (__builtin_popcount(i) != 1) solve_for(i);
		else fill(dp[i], dp[i] + N, 0);
	}

	cout << *min_element(dp[k - 1], dp[k - 1] + N);
	return 0;
}
//به زآن که فروشند چه خواهند خرید
