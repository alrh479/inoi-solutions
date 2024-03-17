#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e5 + 5;
const int M = 1e9 + 7;
const int L = 7;
int dp[N + 5][2 * L], n, m, k, lg[N + 5], T, st[N], fn[N], K[N];
vector<int> adj[N];
string s;

void dfs(int v) {
	st[v] = T++;
	for (auto u: adj[v]) dfs(u);
	fn[v] = T;
}
bool is_par(int p, int v) {
	if (v > m) {
		if (v - p + 1 > m) return true;
		return is_par(m - v + p, m);
	}
	return st[p] <= st[v] && fn[v] <= fn[p];
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	for (int i = 10; i < N; i++) lg[i] = lg[i / 10] + 1;

	cin >> n >> m >> k;
	if (m > 0) {
		cin >> s;
	}
	if (k >= L) {
		cout << 0;
		return 0;
	}

	int t = 0;
	for (int i = 1; i < m; i++) {
		while (t && s[t] != s[i]) t = K[t - 1];
		t += s[t] == s[i];
		K[i] = t;
		adj[t].push_back(i + 1);
	}
	adj[0].push_back(1);
	dfs(0);

	dp[0][0] = 1;
	for (int i = 0; i <= n; i++) {
		for (int l = 0; l < L; l++) {
			for (int j = i + 1, z = 1; j <= n; j += i + 1, z++) {	
				if (!is_par(i + 1, j)) {
					break;
				}
				int t = l + lg[z];
				dp[j][t] += (i + 1 > m ? 26ll : 1ll) * dp[i][l] % M;
				if (dp[j][t] >= M) dp[j][t] -= M;
			}
		}
	}
	cout << dp[n][k];

	return 0;
}
//نرو
