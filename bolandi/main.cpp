#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 1005;
long long dist[N][N];
int h[N], H[N], n, m;
vector<int> adj[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> H[i];
	
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	copy(H, H + n, h);
	sort(h, h + n);
	
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dist[i][j] = INF;
	set<array<long long, 3>> S;
	dist[0][n - 1] = 0;
	S.insert({dist[0][n - 1], 0, n - 1});

	while (S.size()) {
		auto a = *S.begin();
		S.erase(S.begin());
		int v = a[1];
		int t = a[2];

		for (auto u: adj[v]) {
			long long d = dist[v][t] + abs(H[v] - h[t]);
			if (d < dist[u][t]) {
				S.erase({dist[u][t], u, t});
				dist[u][t] = d;
				S.insert({dist[u][t], u, t});
			}
		}
		if (t) {
			if (dist[v][t - 1] > dist[v][t]) {
				S.erase({dist[v][t - 1], v, t - 1});
				dist[v][t - 1] = dist[v][t];
				S.insert({dist[v][t - 1], v, t - 1});
			}
		}
	}
	long long mn = INF;
	for (int i = 0; i < n; i++) 
		mn = min(mn, dist[n - 1][i] + abs(H[n - 1] - h[i]));
	cout << (mn == INF ? -1 : mn) << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
