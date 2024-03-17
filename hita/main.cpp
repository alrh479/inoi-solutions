#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 200 + 5;
const int M = 1e9 + 7;
int dp[N][N], n, m;
vector<int> adj[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	for (int i = 0; i < n; i++) sort(adj[i].begin(), adj[i].end());

	//[l, r]
	for (int l = n - 1; l >= 0; l--) {
		dp[l][l] = 1;
		for (int r = l + 1; r < n; r++) {
			//no edge: 
			dp[l][r] += dp[l][r - 1];

			for (auto x: adj[r]) if (x >= l && x < r) { //n * m
				for (int k = x; k < r; k++) { //n * m * n
					dp[l][r] += dp[l][x] * dp[x][k] % M * dp[k + 1][r] % M;
				}
			}
			dp[l][r] %= M;
		}
	}
	int ans = dp[0][n - 1];
	for (int i = 0; i < n; i++) ans += dp[0][i] * dp[i + 1][n - 1] % M;
	cout << ans % M << '\n';

	return 0;
}
//به زآن که فروشند چه خواهند خرید
//نباید اکسپت بشه ولی حل کردن تایم فقط با تعریف یه دیپی ۲ که ضرب اون وسط رو خساب کنه حل میشه
