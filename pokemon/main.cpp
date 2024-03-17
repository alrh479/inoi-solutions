#include "bits/stdc++.h"
#define int long long
#define arr array<long long, 2>
using namespace std;
const long long INF = 1ll << 60;
const int N = 2e5 + 5;
int dp[N], up[N];
bitset<N> mark;
vector<int> adj[N];
int n, q, V[N], D[N], d[N];

void bala(int v, int p) {
	dp[v] = d[v];
	for (auto u: adj[v]) if (u != p) {
		bala(u, v);
		dp[v] = max(dp[v], dp[u] + 1);
	}
}
void pain(int v, int p) {
	int mx1 = -1, mx2 = -1;
	up[v] = max(up[v], d[v]);

	for (int u: adj[v]) if (u != p) {
		if (mx1 == -1 || dp[u] > dp[mx1]) {
			mx2 = mx1;
			mx1 = u;
		}
		else if (mx2 == -1 || dp[u] > dp[mx2]) {
			mx2 = u;
		}
	}
	
	for (auto u: adj[v]) if (u != p) {
		up[u] = max(up[u], up[v] + 1);

		if (u != mx1 && mx1 != -1) {
			up[u] = max(up[u], dp[mx1] + 2);
		}
		if (u != mx2 && mx2 != -1) {
			up[u] = max(up[u], dp[mx2] + 2);
		}
		pain(u, v);
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	fill(dp, dp + N, -INF);
	fill(d, d + N, -INF);
	fill(up, up + N, -INF);

	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 0; i < q; i++) {
		cin >> V[i] >> D[i]; V[i]--;
		d[V[i]] = -D[i];
	}
	bala(0, 0);
	pain(0, 0);

	for (int i = 0; i < n; i++) {
		d[i] = (max(dp[i], up[i]) <= 0 ? 0 : -INF);
	}

	fill(dp, dp + N, -INF);
	fill(up, up + N, -INF);

	bala(0, 0);
	pain(0, 0);

	for (int i = 0; i < q; i++) {
		assert(max(dp[V[i]], up[V[i]]) <= D[i]);
		if (max(dp[V[i]], up[V[i]]) != D[i]) {
			cout << "-1\n";
			return 0;
		}
	}
	for (int i = 0; i < n; i++)
		cout << (d[i] == -INF ? 0 : 1);

	return 0;
}
//به زآن که فروشند چه خواهند خرید
